//
// Created by Bernie Joyce on 21/04/2026.
//

#include "Hopper.h"

#include <iostream>


void Hopper::move() {
        while (isWayBlocked()) {
                direction_ = static_cast<Direction>(directions(mt));
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
                position.second = position.second < 0 ? 0 : position.second;
        }
        path.push_back(position);
}

void Hopper::display() {
        cout << "Hopper: ";
        Bug::display();
        cout << " " << to_string(hopLength);
}

string Hopper::displayLifeHistory() {
        return to_string(id) + " Hopper Path:" + displayLifeHistoryInitial();
}

string Hopper::displayTypeAndID() {
        return "Hopper" + Bug::displayTypeAndID();
}

void Hopper::takeDamage(int damage) {
        Bug::takeDamage(damage);
}


Hopper::Hopper(const int id, const int x_Coordinate, const int y_Coordinate, const Direction direction,
               const int health, const int hopLength) : Bug(
        id, x_Coordinate, y_Coordinate, direction, health) {
        if (hopLength < 2 || hopLength > 4) {
                throw std::invalid_argument("Hop length must be between 2 and 4");
        }
        this->hopLength = hopLength;
}
