#include "Crawler.h"
#include <iostream>

void Crawler::display() {
        cout << "Crawler:";
        Bug::display();
}

void Crawler::move() {
        {
                while (isWayBlocked()) {
                        direction_ = static_cast<Direction>(directions(mt));
                }
                if (direction_ == west)  position.first--;
                if (direction_ == east)  position.first++;
                if (direction_ == south) position.second++;
                if (direction_ == north) position.second--;
                path.push_back(position);
        }
}

Crawler::Crawler(const int id, const int x_Coordinate, const int y_Coordinate, const Direction direction,
                 const int health) : Bug(id, x_Coordinate, y_Coordinate, direction, health) {
}

string Crawler::displayLifeHistory() {
        return to_string(id) + " Crawler Path:" + displayLifeHistoryInitial();
}

string Crawler::displayTypeAndID() {
         return "Crawler" + Bug::displayTypeAndID();
}

void Crawler::takeDamage(int damage) {
        Bug::takeDamage(damage);
}
