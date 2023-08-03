#include "GEngine.hpp"
#include "Question.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <ostream>
#include <string>
#include <thread>
#include <boost/algorithm/string.hpp>

std::ostream & operator<<(std::ostream & os, const Question & q) {
    os << q.get_category() << "; "
       << q.get_question() << "; "
       << q.get_answer()   << "; "
       << q.get_tips()[0]  << "; "
       << q.get_tips()[1]  << "; "
       << q.get_tips()[2]  << "; "
       << q.get_path_to_wav() << "; "
       << q.is_used() << ";";
    return os;
}

Question GEngine::read_question(std::ifstream & qfs, int number) {
    std::string category;
    std::string question;
    std::string answer;
    std::array<std::string,3> tips;
    std::string path_to_wav;
    bool is_used;
    std::getline(qfs,category,';');
    std::getline(qfs,question,';');
    std::getline(qfs,answer,';');
    std::getline(qfs,tips[0],';');
    std::getline(qfs,tips[1],';');
    std::getline(qfs,tips[2],';');
    std::getline(qfs,path_to_wav,';');
    qfs >> is_used;
    qfs.ignore(1000,'\n');
    boost::algorithm::trim(category);
    boost::algorithm::trim(question);
    boost::algorithm::trim(answer);
    for (auto & x : tips) boost::algorithm::trim(x);
    boost::algorithm::trim(path_to_wav);

    return Question(category,question,answer,tips,path_to_wav,is_used,number);
}

GStateSnap::GStateSnap(std::array<Team,3> _teams, std::vector<Question> _questions_set,
            int _pot, int _oldpot, int _minoldpot, std::array<int,3> _maxpoints,
            int _active_team_max_points, state _current_state, Team * _active_team,
            ekey _active_team_key, int _highest_bid, int _old_highest_bid, 
            int _current_question_ind, bool _category_visible, bool _question_visible,
            bool _tips_visible, int _rand_answ_pos, int _ind, int _blackbox_count) :
    teams(_teams),
    questions_set(_questions_set),
    pot(_pot),
    oldpot(_oldpot),
    minoldpot(_minoldpot),
    maxpoints(_maxpoints),
    active_team_max_points(_active_team_max_points),
    current_state(_current_state),
    active_team(_active_team),
    active_team_key(_active_team_key),
    highest_bid(_highest_bid),
    old_highest_bid(_old_highest_bid),
    current_question_ind(_current_question_ind),
    category_visible(_category_visible),
    question_visible(_question_visible),
    tips_visible(_tips_visible),
    rand_answ_pos(_rand_answ_pos),
    ind(_ind),
    blackbox_count(_blackbox_count),
    question_nr(0)
{}

std::tuple<std::array<Team,3>,std::vector<Question>,int,int,int,std::array<int,3>,
           int,state,Team*,ekey,int,int,int,bool,bool,bool,int,int,int> GStateSnap::get_data() 
{
    return std::make_tuple(teams,questions_set,pot,oldpot,minoldpot,maxpoints,
                 active_team_max_points,current_state,active_team,
                 active_team_key,highest_bid,old_highest_bid,
                 current_question_ind,category_visible,
                 question_visible,tips_visible,
                 rand_answ_pos,ind,blackbox_count);
}


GEngine::GEngine(GEngineLocInterface * localization, SoundPlayerInterface * _sound_player, std::ofstream & _outf, 
                 std::array<Team,3> _teams, uint time2answer, uint tip_freq, std::vector<int> blackb, 
                 std::string _prefix_to_path, bool fixed_order) : 
    GStateSnap(_teams,
                std::vector<Question>(), //questions_set
                0, 0, 0, //pot, oldpot, minoldpot
                {0,0,0}, 0, //maxpoints, active_team_max_points
                state::idle, //current_state
                nullptr, ekey::unknown, //active_team, active_team_key
                0, 0, -1, //highest_bid, old_highest_bid, current_question_ind
                false, false, false, //visible : category, question, tips
                -1, -1, blackb[0] // rand_answ_pos, ind, blackbox_count
            ),
    loc(localization),
    sound_player(_sound_player),
    outf(_outf),
    prefix_to_path(_prefix_to_path),
    tip_buy_tresh(tip_freq),
    bb_buy_tresh(blackb[1]),
    tbq(-1),
    timer(time2answer),
    fixed_q_order(fixed_order)
{
    rand_gen = std::mt19937(rand_dev());
    rand_tip = std::uniform_int_distribution<int>(0,3);
    rand_tip_bb_to_buy = std::uniform_real_distribution<double>(0,100);
}

GEngine::GEngine(GEngineLocInterface * localization, SoundPlayerInterface * _sound_player, std::ifstream & qf, 
                 std::ofstream & _outf, std::array<Team,3> _teams, std::vector<std::string> Inc, 
                 std::vector<std::string> Exc, uint time2answer, uint tip_freq, std::vector<int> blackb, 
                 bool exclude_musical, std::string _prefix_to_path, bool fixed_order) : 
    GEngine(localization,_sound_player,_outf,_teams,time2answer,tip_freq,blackb,_prefix_to_path, fixed_order) 
{
    questions_set.push_back(Question(loc->strTip(),"","",{"","",""},"",false,0));
    for (int i=1;!qf.eof();++i) {
        Question tmp = read_question(qf, i);
        if (!qf) {
            qf.clear();
            qf.ignore(1000,'\n');
            continue;
        }
        tmp.add_prefix_to_path(prefix_to_path);
        if (tmp.is_used() 
            || (!Exc.empty() && std::find(Exc.begin(), Exc.end(), tmp.get_category()) != Exc.end())
            || (exclude_musical && tmp.is_musical_q()))
        {
            used_questions_set.push_back(tmp);
        }
        else if (Inc.empty() || std::find(Inc.begin(), Inc.end(),tmp.get_category()) != Inc.end())
            questions_set.push_back(tmp);
        else 
            used_questions_set.push_back(tmp);
    }
    std::stable_sort(used_questions_set.begin(),used_questions_set.end(),[&](auto & q1, auto & q2){return static_cast<int>(q1.is_used()) < static_cast<int>(q2.is_used());});
    all_questions_nr = questions_set.size()-1;
    rand_quest = std::uniform_int_distribution<int>(1,all_questions_nr);
}

void GEngine::add_snap() {
    snaps.push(GStateSnap(teams,questions_set,pot,oldpot,minoldpot,
                          maxpoints,active_team_max_points,current_state,
                          active_team,active_team_key,highest_bid,
                          old_highest_bid,current_question_ind,
                          category_visible,question_visible,tips_visible,
                          rand_answ_pos,ind,blackbox_count));
}

void GEngine::use_last_snap() {
    if (!snaps.empty()) {
        timer.stop();
        timer.reset();
        std::tie(teams,questions_set,pot,oldpot,minoldpot,maxpoints,
                 active_team_max_points,current_state,active_team,
                 active_team_key,highest_bid,old_highest_bid,
                 current_question_ind,category_visible,
                 question_visible,tips_visible,
                 rand_answ_pos,ind,blackbox_count) = snaps.top().get_data();
        rand_quest = std::uniform_int_distribution<int>(1,questions_set.size()-1);
        snaps.pop();
    }
}

bool GEngine::is_any_team_va_banque() const {
    bool ans = false;
    for (auto & x : teams) {
        if (x.va_banque_val() == x.get_points_invested() && x.va_banque_val() > 0) {
            ans = true;
        }
        if (x.get_points_invested() >= va_banque_tab[1]) {
            ans = true;
        }
    }
    return ans;
}

bool GEngine::chooseActiveTeam(ekey key) {
    bool ans = false;
    switch (key) {
        case ekey::z : {
            if (teams[0].va_banque_val() > highest_bid && !is_any_team_va_banque()) {
                active_team = &teams[0];
                ans = true;
            }
        };break;
        case ekey::x : {
            if (teams[1].va_banque_val() > highest_bid && !is_any_team_va_banque()) {
                active_team = &teams[1];
                ans = true;
            }
        };break;
        case ekey::c : {
            if (teams[2].va_banque_val() > highest_bid && !is_any_team_va_banque()) {
                active_team = &teams[2];
                ans = true;
            }
        };break;
    }
    return ans;
}

void GEngine::ready_to_lic() {
    for (auto & x : teams)
        x.invest_points(200);
    old_highest_bid = 200;
    highest_bid = 200;
}

void GEngine::licitation(ekey key) {
    if (key == active_team_key) {
        if (active_team->get_points_invested() < va_banque_tab[0]) {
            active_team->invest_points(va_banque_tab[0] - active_team->get_points_invested());
        }
        else if (active_team->get_points_invested() < va_banque_tab[1]) {
            active_team->invest_points(va_banque_tab[1] - active_team->get_points_invested());                    
        }
    } else if (key == ekey::up) {
        active_team->invest_points(100);
    } else if (key == ekey::down) {
        active_team->return_investment(100,old_highest_bid+100);         
    } else if (key == ekey::z || key == ekey::x || key == ekey::c) {
        if (chooseActiveTeam(key)) {
            active_team->invest_points(highest_bid - active_team->get_points_invested() + 100);
            old_highest_bid = highest_bid;
            active_team_key = key;
        }
        resetallhighlight();
        active_team->sethlight();
    }
}

void GEngine::perform_action(ekey key) {
    va_banque_tab = {teams[0].va_banque_val(),teams[1].va_banque_val(),teams[2].va_banque_val()};
    std::sort(va_banque_tab.begin(),va_banque_tab.end());
    if (key == ekey::u) {
        if (is_any_snap())
            use_last_snap();
    } else {
        add_snap();
    }
    switch (current_state) {
        case state::idle : {
            if (key == ekey::p) {
                for (int i=0;i<3;++i) {
                    maxpoints[i] = teams[i].get_points();
                }
                ind = -1;
                current_state = state::punishment;
            }
            if (key == ekey::enter) {
                category_visible = true;
                tbq = tip_bb_question();
                if(tbq == 1) {
                    current_question_ind = 0;
                    questions_set[0] = Question(loc->strTip(),"","",{"","",""},"",false,0);
                    current_state = state::tip_buy;
                } else if (tbq == 2 && blackbox_count > 0) {
                    current_question_ind = 0;
                    questions_set[0] = Question(loc->strBlackBox(),"","",{"","",""},"",false,0);
                    blackbox_count--;
                    current_state = state::tip_buy;
                }
                else {
                    current_question_ind = get_rand_question_ind();
                    current_state = state::category;
                }
            }
            if (key == ekey::h) {
                category_visible = true;
                current_question_ind = 0;
                questions_set[0] = Question(loc->strTip(),"","",{"","",""},"",false,0);
                current_state = state::tip_buy;
            }
            if (key == ekey::e) {
                category_visible = true;
                current_question_ind = 0;
                questions_set[0] = Question(loc->strBlackBox(),"","",{"","",""},"",false,0);
                if (blackbox_count > 0) 
                    blackbox_count--;
                current_state = state::tip_buy;
            }
        };break;
        case state::punishment : {
            if (key == ekey::z) {
                active_team = &teams[0];
                ind = 0;
            }
            if (key == ekey::x) {
                active_team = &teams[1];
                ind = 1;
            }
            if (key == ekey::c) {
                active_team = &teams[2];
                ind = 2;
            }
            if (key == ekey::down && active_team) {
                if (active_team->get_points() > 0)
                    active_team->take_points(100);
            }
            if (key == ekey::up && active_team) {
                if (active_team->get_points() < maxpoints[ind])
                    active_team->give_points(100);
            }
            if (key == ekey::enter) {
                category_visible = true;
                tbq = tip_bb_question();
                if(tbq == 1) {
                    current_question_ind = 0;
                    questions_set[0] = Question(loc->strTip(),"","",{"","",""},"",false,0);
                    current_state = state::tip_buy;
                } else if (tbq == 2 && blackbox_count > 0) {
                    current_question_ind = 0;
                    questions_set[0] = Question(loc->strBlackBox(),"","",{"","",""},"",false,0);
                    blackbox_count--;
                    current_state = state::tip_buy;
                }
                else {
                    current_question_ind = get_rand_question_ind();
                    current_state = state::category;
                }
            }
            if (key == ekey::h) {
                category_visible = true;
                current_question_ind = 0;
                questions_set[0] = Question(loc->strTip(),"","",{"","",""},"",false,0);
                current_state = state::tip_buy;
            }
            if (key == ekey::e) {
                category_visible = true;
                current_question_ind = 0;
                questions_set[0] = Question(loc->strBlackBox(),"","",{"","",""},"",false,0);
                if (blackbox_count > 0) 
                    blackbox_count--;
                current_state = state::tip_buy;
            }
        };break;
        case state::category : {
            if (key == ekey::e) {
                minoldpot = oldpot;
                current_state = state::extra_pot;
            }
            if (key == ekey::enter) {
                ready_to_lic();
                current_state = state::start_lic;
            }
        };break;
        case state::extra_pot : {
            if (key == ekey::up) {
                oldpot += 100;
            }
            if (key == ekey::down) {
                if (oldpot > minoldpot)
                    oldpot -= 100;
            }
            if (key == ekey::enter) {
                ready_to_lic();
                current_state = state::start_lic;
            }
        };break;
        case state::tip_buy : {
            licitation(key);
            if (key == ekey::enter) {
                if (active_team) {
                    active_team->reset_points_invested();
                    for (auto & x : teams) {
                        x.give_points(x.get_points_invested());
                        x.reset_points_invested();
                    }
                }
                reset_vars();
                current_state = state::idle;
            }
        };break;
        case state::start_lic : {
            if (chooseActiveTeam(key)) { 
                resetallhighlight();
                active_team->sethlight();
                active_team->invest_points(highest_bid - active_team->get_points_invested() + 100);
                old_highest_bid = highest_bid;
                active_team_key = key;
                current_state = state::lic;
            }
        };break;
        case state::lic : {
            licitation(key);
            if (key == ekey::enter) {
                current_state = state::sold;
            }
        };break;
        case state::sold : {
            if (key == ekey::enter) {
                if (get_current_question().is_musical_q()) {
                    sound_player->play(get_current_question().get_path_to_wav());
                    current_state = state::music_question;
                } else {
                question_visible = true;
                timer.run();
                active_team_max_points = active_team->get_points();
                current_state = state::question;
                }
            }
        };break;
        case state::music_question : {
            if (key == ekey::enter) {
                sound_player->stop();
                question_visible = true;
                timer.run();
                active_team_max_points = active_team->get_points();
                current_state = state::question;
            }            
        };break;
        case state::question : {
            if (key == ekey::h) {
                if (!tips_visible) {
                    rand_answ_pos = get_rand_tip_pos();
                    timer.reset();
                    tips_visible = true;
                }
            }
            if (key == ekey::a) {
                active_team->give_points(pot);
                oldpot=0;
                remove_question(current_question_ind);
                reset_vars();
                if (!is_questions_set_empty())
                    current_state = state::idle;
                else
                    current_state = state::end;
            }
            if (key == ekey::d) {
                oldpot=pot;
                remove_question(current_question_ind);
                reset_vars();
                if (!is_questions_set_empty())
                    current_state = state::idle;
                else
                    current_state = state::end;
            }
            if (key == ekey::s) {
                if (timer.is_runnung())
                    timer.stop();
                else
                    timer.run();
            }
            if (key == ekey::down) {
                if (active_team->get_points() > 0)
                    active_team->take_points(100);
            }
            if (key == ekey::up) {
                if (active_team->get_points() < active_team_max_points)
                    active_team->give_points(100);
            }
        }
        case state::end : {

        }
    }
    if (active_team) {
        highest_bid = active_team->get_points_invested();
    }
    if (current_state != state::tip_buy)
        pot = teams[0].get_points_invested() + teams[1].get_points_invested() + teams[2].get_points_invested() + oldpot;
}

std::array<std::string,4> GEngine::get_tips() const {
    std::array<std::string,4> ans;
    if (is_tips_visible()) {
        std::array<std::string,3> tips = get_current_question().get_tips();
        for (int i=0, j=0;i<4;++i) {
            if (i == rand_answ_pos)
                ans[i] = get_current_question().get_answer();
            else 
                ans[i] = tips[j++];
        }
    }
    return ans;
}

int GEngine::get_rand_question_ind() {
    question_nr++;
    return fixed_q_order ? 1 : rand_quest(rand_gen);
}


int GEngine::tip_bb_question() {
    double num = rand_tip_bb_to_buy(rand_gen);
    if (num < tip_buy_tresh)
        return 1;
    else if (num < tip_buy_tresh+bb_buy_tresh)
        return 2;
    else
        return 0;
}

void GEngine::reset_vars() {
    active_team = nullptr;
    active_team_key = ekey::unknown;
    resetallinvestedpoints();
    resetallhighlight();
    category_visible = false;
    question_visible = false;
    tips_visible = false;
    current_question_ind = -1;
    rand_answ_pos = -1;
    highest_bid = 0;
    tbq = -1;
    timer.stop();
    timer.reset();
    for (auto & x : teams) {
        if (x.get_points() < 300)
            x.take_points(x.get_points());
    }
}

std::vector<std::string> GEngine::get_all_categories() const {
    std::vector<std::string> ans;
    for (auto & x : questions_set) {
        ans.push_back(x.get_category());
    }
    return ans;
}

void GEngine::remove_question(int ind) {
    questions_set[ind].set_as_used();
    used_questions_set.push_back(questions_set[ind]);
    questions_set.erase(questions_set.begin()+ind);
    if (!is_questions_set_empty())
        rand_quest = std::uniform_int_distribution<int>(1,questions_set.size()-1);
}

GEngine::~GEngine() {
    if (current_question_ind > 0 && current_state == state::question)
        remove_question(current_question_ind);
    questions_set.erase(questions_set.begin());
    for (auto & x : questions_set) {
        x.remove_prefix_to_path(prefix_to_path);
        outf << x << std::endl;
    }
    outf << std::endl;
    for (auto & x: used_questions_set) {
        x.remove_prefix_to_path(prefix_to_path);   
        outf << x << std::endl;
    }
    std::cout << "-1 " << teams[0] << std::endl;
    std::cout << "-2 " << teams[1] << std::endl;
    std::cout << "-3 " << teams[2] << std::endl;
}