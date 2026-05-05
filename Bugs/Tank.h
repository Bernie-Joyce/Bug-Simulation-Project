//
// Created by Bernie Joyce on 05/05/2026.
//

#ifndef A_BUGS_LIFE_TANK_H
#define A_BUGS_LIFE_TANK_H
#include "Bug.h"


class Tank : public Bug{
private:
        int defense;
public:
        Tank(int id, int x_Coordinate, int y_Coordinate, Direction direction, int health, int defense);
        int getDefense();
        void setDefense(int defense);
        void display() override;
        void move() override;
        void displayLifeHistory() override;
        void displayTypeAndID() override;
        void takeDamage(int damage) override;
};



#endif //A_BUGS_LIFE_TANK_H
