//
// Created by Bernie Joyce on 21/04/2026.
//

#include "Hopper.h"

void Hopper::move() {
        if (isWayBlocked()) {
                bool wayIsBlocked = true;
                while (wayIsBlocked) {
                        direction_ = static_cast<Direction>(rand() % 4);
                        if (!isWayBlocked()) {
                                wayIsBlocked = false;
                        }
                }
        } else {
                if (direction_ == west) {
                        position.first = position.first - hopLength;
                        position.first = (position.first < 0) ? 0 : position.first;
                }
                if (direction_ == east) {
                        position.first = position.first + hopLength;
                        position.first = (position.first > 9) ? 9 : position.first;
                }
                if (direction_ == south) {
                        position.second = position.second - hopLength;
                        position.second = (position.second < 0) ? 0 : position.second;
                }
                if (direction_ == north) {
                        position.second = position.second + hopLength;
                        position.second = (position.second > 9) ? 9 : position.second;
                }
                path.push_back(position);
        }
}
