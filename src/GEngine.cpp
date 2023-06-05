#include "GEngine.hpp"

Question GEngine::read_question(std::ifstream & qfs, int number) {
    std::string category;
    std::string question;
    std::string answer;
    std::array<std::string,3> tips;
    std::getline(qfs,category,';');
    std::getline(qfs,question,';');
    std::getline(qfs,answer,';');
    std::getline(qfs,tips[0],';');
    std::getline(qfs,tips[1],';');
    std::getline(qfs,tips[2],';');
    qfs.ignore(1000,'\n');
    return Question(category,question,answer,tips,number);
}

GStateSnap::GStateSnap(std::array<Team,3> _teams, std::vector<Question> _questions_set,
            int _pot, int _oldpot, int _minoldpot, std::array<int,3> _maxpoints,
            int _active_team_max_points, state _current_state, Team * _active_team,
            ekey _active_team_key, int _highest_bid, int _old_highest_bid, 
            int _current_question_ind, bool _category_visible, bool _question_visible,
            bool _tips_visible, int _rand_answ_pos, int _ind) :
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
    ind(_ind)
{}

std::tuple<std::array<Team,3>,std::vector<Question>,int,int,int,std::array<int,3>,
           int,state,Team*,ekey,int,int,int,bool,bool,bool,int,int> GStateSnap::get_data() 
{
    return std::make_tuple(teams,questions_set,pot,oldpot,minoldpot,maxpoints,
                 active_team_max_points,current_state,active_team,
                 active_team_key,highest_bid,old_highest_bid,
                 current_question_ind,category_visible,
                 question_visible,tips_visible,
                 rand_answ_pos,ind);
}


GEngine::GEngine() : 
    GStateSnap({Team("niebiescy","#19247C","#007FFF",5000),
                Team("zieloni","#006633","#33CC66",3000),
                Team("żółci","#C0A62C","#F9E04B",1000)},
                std::vector<Question>(), //questions_set
                0, 0, 0, //pot, oldpot, minoldpot
                {0,0,0}, 0, //maxpoints, active_team_max_points
                state::idle, //current_state
                nullptr, ekey::unknown, //active_team, active_team_key
                0, 0, -1, //highest_bid, old_highest_bid, current_question_ind
                false, false, false, //visible : category, question, tips
                -1, -1 // rand_answ_pos, ind
            ),
    timer(60)
{
    rand_gen = std::mt19937(rand_dev());
    rand_tip = std::uniform_int_distribution<int>(0,3);
    rand_tip_to_buy = std::uniform_int_distribution<int>(0,9);
}

GEngine::GEngine(std::ifstream & qf) : GEngine() {
    questions_set.push_back(Question("Podpowiedź","","",{"","",""},0));
    for (int i=1;!qf.eof();++i) {
        questions_set.push_back(read_question(qf,i));
    }
    rand_quest = std::uniform_int_distribution<int>(1,questions_set.size()-1);
}

void GEngine::add_snap() {
    snaps.push(GStateSnap(teams,questions_set,pot,oldpot,minoldpot,
                          maxpoints,active_team_max_points,current_state,
                          active_team,active_team_key,highest_bid,
                          old_highest_bid,current_question_ind,
                          category_visible,question_visible,tips_visible,
                          rand_answ_pos,ind));
}

void GEngine::use_last_snap() {
    if (!snaps.empty()) {
        std::tie(teams,questions_set,pot,oldpot,minoldpot,maxpoints,
                 active_team_max_points,current_state,active_team,
                 active_team_key,highest_bid,old_highest_bid,
                 current_question_ind,category_visible,
                 question_visible,tips_visible,
                 rand_answ_pos,ind) = snaps.top().get_data();
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
                if(is_tip_to_buy()) {
                    current_question_ind = 0;
                    current_state = state::tip_buy;
                }
                else {
                    current_question_ind = get_rand_question_ind();
                    current_state = state::category;
                }
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
                if(is_tip_to_buy()) {
                    current_question_ind = 0;
                    current_state = state::tip_buy;
                }
                else {
                    current_question_ind = get_rand_question_ind();
                    current_state = state::category;
                }
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
                question_visible = true;
                timer.run();
                active_team_max_points = active_team->get_points();
                current_state = state::question;
            }
        };break;
        case state::question : {
            if (key == ekey::t) {
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
    questions_set.erase(questions_set.begin()+ind);
    if (!is_questions_set_empty())
        rand_quest = std::uniform_int_distribution<int>(1,questions_set.size()-1);
}