//
// Created by Bernie Joyce on 21/04/2026.
//

#include "Hopper.h"

#include <iostream>


void Hopper::move() {
        while (isWayBlocked()) {
                bool wayIsBlocked = true;
                while (wayIsBlocked) {
                        direction_ = static_cast<Direction>(directions(mt));
                        if (!isWayBlocked()) {
                                wayIsBlocked = false;
                        }
                }
        }
        if (direction_ == west) {
                position.first = position.first - hopLength;
                position.first = position.first < 0 ? 0 : position.first;
        }
        if (direction_ == east) {
                position.first = position.first + hopLength;
                position.first = position.first > 9 ? 9 : position.first;
        }
        if (direction_ == south) {
                position.second = position.second + hopLength;
                position.second = position.second > 9 ? 9 : position.second;
        }
        if (direction_ == north) {
                position.second = position.second - hopLength;
                position.second = position.second > 0 ? 0 : position.second;
        }
        path.push_back(position);
}

void Hopper::display() {
        const vector<string> directionsList = {"north", "south", "east", "west"};
        cout << std::boolalpha << "Hopper:\nID: " << to_string(id) << "\nPosition: " << to_string(position.first) << ","
                        << to_string(position.second) << "\nDirection: " << directionsList[direction_]
                        << "\nHealth: " << to_string(health)
                        << "\nAlive: " << alive
                        << "\nHop Length: " << to_string(hopLength);
}

Hopper::Hopper(int id, int x_Coordinate, int y_Coordinate, Direction direction, int health, int hopLength) {
        if (x_Coordinate < 0 || x_Coordinate > 9) {
                throw std::invalid_argument("x_Coordinate must be between 0 and 9");
        }
        if (y_Coordinate < 0 || y_Coordinate > 9) {
                throw std::invalid_argument("Y_Coordinate must be between 0 and 9");
        }
        if (health < 1 || health > 20) {
                throw std::invalid_argument("Health must between 1 and 20");
        }
        if (hopLength < 2 || hopLength > 4) {
                throw std::invalid_argument("Hop length must be between 2 and 4");
        }
        this->id = id;
        this->position.first = x_Coordinate;
        this->position.second = y_Coordinate;
        this->direction_ = direction;
        this->health = health;
        this->hopLength = hopLength;
}
