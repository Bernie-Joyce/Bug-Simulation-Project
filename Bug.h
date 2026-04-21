//
// Created by Bernie Joyce on 21/04/2026.
//

#ifndef A_BUGS_LIFE_BUG_H
#define A_BUGS_LIFE_BUG_H
#include <list>
#include <utility>
using namespace std;

enum Direction {
        north,
        south,
        east,
        west,
};

class Bug {
protected:
        int id {};
        pair<int,int> position;
        Direction direction_ {};
        int health {};
        bool alive {true};
        list<pair<int, int>> path;
        virtual void move() {}
        bool isWayBlocked() {
                if (position.first==0 && direction_==west) {
                        return true;
                }
                if (position.first==9 && direction_==east){
                        return true;
                }
                if (position.second==0 && direction_==south) {
                        return true;
                }
                if (position.second==9 && direction_==north) {
                        return true;
                }
                return false;
        }
};
#endif //A_BUGS_LIFE_BUG_H