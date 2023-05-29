#include "Team.hpp"

bool Team::invest_points(int amount) {
    if (amount < 0) return false;
    if ((points - amount) >= 0) {
        points -= amount;
        invested += amount;
        return true;
    }
    return false;
}
bool Team::return_investment (int amount, int other_max) {
    if (amount < 0) return false;
    if ((invested - amount) >= other_max) {
        invested -= amount;
        points += amount;
        return true;
    }
    return false;
}