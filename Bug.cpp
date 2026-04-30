//
// Created by Bernie Joyce on 21/04/2026.
//

#include "Bug.h"

#include <iostream>

bool Bug::isWayBlocked() const {
        {
                if (position.first == 0 && direction_ == west) {
                        return true;
                }
                if (position.first == 9 && direction_ == east) {
                        return true;
                }
                if (position.second == 9 && direction_ == south) {
                        return true;
                }
                if (position.second == 0 && direction_ == north) {
                        return true;
                }
                return false;
        }
}


Bug::Bug(int id, int x_Coordinate, int y_Coordinate, Direction direction, int health) {
        if (x_Coordinate < 0 || x_Coordinate > 9) {
                throw std::invalid_argument("x_Coordinate must be between 0 and 9");
        }
        if (y_Coordinate < 0 || y_Coordinate > 9) {
                throw std::invalid_argument("Y_Coordinate must be between 0 and 9");
        }
        if (health < 1 || health > 20) {
                throw std::invalid_argument("Health must between 1 and 20");
        }
        this->id = id;
        this->position.first = x_Coordinate;
        this->position.second = y_Coordinate;
        this->direction_ = direction;
        this->health = health;
}

int Bug::getId() const {
        return this->id;
}

void Bug::display() {
        const vector<string> directionsList = {"North", "South", "East", "West"};
        string alive_str = alive ? "Alive" : "Dead";

        cout << " " << to_string(id) << " "
                        << " (" << to_string(position.first) << "," << to_string(position.second) << ") "
                        << to_string(health) <<
                        " " <<
                        directionsList[direction_]
                        << " " << alive_str;
}
