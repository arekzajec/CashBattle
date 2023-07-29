#ifndef TEAM_HPP
#define TEAM_HPP

#include <string>
#include <vector>
#include <iostream>

class Team {
    std::string name;
    std::string color;
    std::string hcolor;
    int points;
    int invested;
    bool highlighted;
public:
    Team() = delete;
    Team(std::string _name, std::string _color, 
         std::string _hcolor, int _points = 5000) : 
        name(_name), 
        color(_color), 
        hcolor(_hcolor), 
        points(_points), 
        invested(0), 
        highlighted(false) 
    {}
    Team(std::vector<std::string> in) : Team(in[0],in[1],in[2],std::stod(in[3])) {}
    std::string get_name() const {return name;};
    std::string get_color() const {return color;};
    std::string get_hcolor() const {return hcolor;};
    int get_points() const {return points;};
    void take_points(int amount) {if (amount>0) points -= amount;};
    void give_points(int amount) {if (amount>0) points += amount;};
    int get_points_invested() const {return invested;};
    bool invest_points(int amount);
    bool return_investment (int amount, int other_max);
    void reset_points_invested() {invested = 0;};
    bool ishighlighted() const {return highlighted;};
    void sethlight() {highlighted = true;};
    void resethlight() {highlighted = false;};
    int va_banque_val() const {return points + invested;};
};

std::ostream & operator<< (std::ostream & os, const Team & T);

#endif