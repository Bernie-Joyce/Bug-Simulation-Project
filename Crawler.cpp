//
// Created by Bernie Joyce on 21/04/2026.
//

#include "Crawler.h"

void Crawler::move() {
        {
                if (isWayBlocked()) {
                        bool wayIsBlocked = true;
                        while (wayIsBlocked) {
                                direction_ = static_cast<Direction>(rand() % 4);
                                if (!isWayBlocked()) {
                                        wayIsBlocked=false;
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