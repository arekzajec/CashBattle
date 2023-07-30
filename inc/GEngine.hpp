#ifndef GENGINE_HPP
#define GENGINE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include "Question.hpp"
#include "Team.hpp"
#include "Timer.hpp"
#include <stack>
#include <tuple>
#include "SoundPlayer.hpp"

enum class state {idle, punishment, category, tip_buy,extra_pot, start_lic, lic, sold, music_question, question, end};
enum class ekey {unknown, z, x, c, enter, up, down, t, a, d, p, e, s, u};

class GStateSnap {
protected:
    std::array<Team,3> teams;
    std::vector<Question> questions_set;
    std::vector<Question> used_questions_set;
    int pot;
    int oldpot;
    int minoldpot;
    std::array<int,3> maxpoints;
    int active_team_max_points;
    state current_state;
    Team * active_team;
    ekey active_team_key;
    int highest_bid;
    int old_highest_bid;
    int current_question_ind;
    bool category_visible;
    bool question_visible;
    bool tips_visible;
    int rand_answ_pos;
    int ind;
public:
    GStateSnap(std::array<Team,3> _teams, std::vector<Question> _questions_set,
               int _pot, int _oldpot, int _minoldpot, std::array<int,3> _maxpoints,
               int _active_team_max_points, state _current_state, Team * _active_team,
               ekey _active_team_key, int _highest_bid, int _old_highest_bid, 
               int _current_question_ind, bool _category_visible, bool _question_visible,
               bool _tips_visible, int _rand_answ_pos, int _ind);
    std::tuple<std::array<Team,3>,std::vector<Question>,int,int,int,std::array<int,3>,
               int,state,Team*,ekey,int,int,int,bool,bool,bool,int,int> get_data();
};

class GEngine : public GStateSnap {
    SoundPlayerInterface * sound_player;
    std::ofstream & outf;
    std::string prefix_to_path;
    std::random_device rand_dev;
    std::mt19937 rand_gen;
    std::uniform_int_distribution<int> rand_quest;
    std::uniform_int_distribution<int> rand_tip;
    std::uniform_int_distribution<int> rand_tip_to_buy;
    Timer timer;

    std::array<int,3> va_banque_tab;

    std::stack<GStateSnap> snaps;

    Question read_question(std::ifstream & qfs, int number);
    void resetallhighlight() {for (auto & x : teams) x.resethlight();}
    void resetallinvestedpoints() {for (auto & x: teams) x.reset_points_invested();}
    bool chooseActiveTeam(ekey key);
    int get_rand_question_ind() {return rand_quest(rand_gen);}
    int get_rand_tip_pos() {return rand_tip(rand_gen);}
    bool is_tip_to_buy() {return (rand_tip_to_buy(rand_gen)?false:true);}
    void reset_vars();
    void ready_to_lic();
    void licitation(ekey key);
    void add_snap();
    void remove_question(int ind);
    bool is_questions_set_empty() {return questions_set.size() <= 1;}
    void use_last_snap();
    int end_max_points();
    GEngine(SoundPlayerInterface * _sound_player, std::ofstream & _outf, std::array<Team,3> _teams, uint time2answer = 60, uint tip_freq = 10, std::string _prefix_to_path = "sound/");
public:
    GEngine(SoundPlayerInterface * _sound_player, std::ifstream & qf, std::ofstream & _outf, std::array<Team,3> _teams, std::vector<std::string> Inc, std::vector<std::string> Exc, uint time2answer = 60, uint tip_freq = 10, bool exclude_musical = false, std::string _prefix_to_path = "sound/");
    const Team & get_team(uint ind) const {return teams[ind];}
    int get_pot() const {return pot;}
    bool is_any_team_va_banque() const;
    void perform_action(ekey key);
    state get_current_state() const {return current_state;}
    const Question & get_current_question() const {return questions_set[current_question_ind];}
    std::vector<std::string> get_all_categories() const;
    bool is_category_visible() const {return category_visible;}
    bool is_question_visible() const {return question_visible;}
    bool is_tips_visible() const {return tips_visible;}
    std::array<std::string,4> get_tips() const;
    int get_time_left() const {return timer.get_sec_left();}
    Team * get_active_team() {return active_team;}
    int get_va_banque_tab_val(int ind) const {return va_banque_tab[ind];}
    bool is_timer_runnung() const {return timer.is_runnung();}
    bool is_any_snap() const {return !snaps.empty();}
    virtual ~GEngine();
};


#endif