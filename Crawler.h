//
// Created by Bernie Joyce on 21/04/2026.
//

#ifndef A_BUGS_LIFE_CRAWLER_H
#define A_BUGS_LIFE_CRAWLER_H
#include "Bug.h"


class Crawler : public Bug {
public:
        void move() override;
        void display() override;
        Crawler(int id, int x_Coordinate, int y_Coordinate, Direction direction, int health);
};


#endif //A_BUGS_LIFE_CRAWLER_H
