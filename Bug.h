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
public:
        virtual ~Bug() = default;
        virtual void display()=0;
protected:
        int id {};
        pair<int,int> position;
        Direction direction_ {};
        int health {};
        bool alive {true};
        list<pair<int, int>> path;
        virtual void move()= 0;
        bool isWayBlocked() const;

};
#endif //A_BUGS_LIFE_BUG_H