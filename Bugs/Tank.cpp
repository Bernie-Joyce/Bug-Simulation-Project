//
// Created by Bernie Joyce on 05/05/2026.
//

#include "Tank.h"

#include <iostream>

Tank::Tank(int id, int x_Coordinate, int y_Coordinate, Direction direction, int health, int defense) : Bug(
        id, x_Coordinate, y_Coordinate, direction, health) {
        if (defense < 1 || defense > 3) {
                throw std::invalid_argument("Defense must be between 1 and 3");
        }
        this->defense = defense;
}

int Tank::getDefense() {
        return this->defense;
}

void Tank::setDefense(int defense) {
        this->defense = defense;
}

void Tank::display() {
        cout << "Tank:";
        Bug::display();
        cout << " " << to_string(defense);
}

void Tank::move() {
        while (isWayBlocked()) {
                direction_ = static_cast<Direction>(directions(mt));
        }
        if (direction_ == west) {
                position.first = position.first - 1;
        }
        if (direction_ == east) {
                position.first = position.first + 1;
        }
        if (direction_ == south) {
                position.second = position.second + 1;
        }
        if (direction_ == north) {
                position.second = position.second - 1;
        }
        path.push_back(position);
}

void Tank::displayLifeHistory() {
        cout << to_string(id) << " Tank Path:";
        displayLifeHistoryInital();
}

void Tank::displayTypeAndID() {
        cout << "Tank";
        Bug::displayTypeAndID();
}

void Tank::takeDamage(int damage) {
        damage = damage - getDefense();
        if (damage < 0) {
                damage = 0;
        }
        Bug::takeDamage(damage);
}
