//
// Created by Bernie Joyce on 05/05/2026.
//

#include "Tank.h"

Tank::Tank(int id, int x_Coordinate, int y_Coordinate, Direction direction, int health, int defense) : Bug(
        id, x_Coordinate, y_Coordinate, direction, health) {
        this->defense = defense;
}

int Tank::getDefense() {
        return this->defense;
}

void Tank::setDefense(int defense) {
        this->defense = defense;
}
