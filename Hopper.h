//
// Created by Bernie Joyce on 21/04/2026.
//

#ifndef A_BUGS_LIFE_HOPPER_H
#define A_BUGS_LIFE_HOPPER_H
#include "Bug.h"


class Hopper : public Bug{
        int hopLength;
public:
        void move() override;

};


#endif //A_BUGS_LIFE_HOPPER_H