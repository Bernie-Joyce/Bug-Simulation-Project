//
// Created by Bernie Joyce on 21/04/2026.
//

#include "Crawler.h"

#include <iostream>
#include "Hopper.cpp"

void Crawler::display() {
        const vector<string> directions = {"north", "south", "east", "west"};

        cout << std::boolalpha << "Crawler:\nID: " << to_string(id) << "\nPosition: " << to_string(position.first) <<
                        ","
                        << to_string(position.second) << "\nDirection: " << directions[direction_]
                        << "\nHealth: " << to_string(health)
                        << "\nAlive: " << to_string(alive);
}

void Crawler::move() {
        {
                if (isWayBlocked()) {
                        bool wayIsBlocked = true;
                        while (wayIsBlocked) {
                                direction_ = static_cast<Direction>(directions(mt));
                                if (!isWayBlocked()) {
                                        wayIsBlocked = false;
                                }
                        }
                } else {
                        if (direction_ == west) {
                                position.first = position.first - 1;
                        }
                        if (direction_ == east) {
                                position.first = position.first + 1;
                        }
                        if (direction_ == south) {
                                position.second = position.second - 1;
                        }
                        if (direction_ == north) {
                                position.second = position.second + 1;
                        }
                        path.push_back(position);
                }
        }
}

Crawler::Crawler(const int id, const int x_Coordinate, const int y_Coordinate, const Direction direction,
                 const int health) {
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
