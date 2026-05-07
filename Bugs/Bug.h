//
// Created by Bernie Joyce on 21/04/2026.
//

#ifndef A_BUGS_LIFE_BUG_H
#define A_BUGS_LIFE_BUG_H
#include <list>
#include <utility>
#include <random>
using namespace std;

enum Direction {
        north,
        south,
        east,
        west,
};

inline std::mt19937 mt{
        static_cast<std::mt19937::result_type>(
                std::chrono::steady_clock::now().time_since_epoch().count()
        )
};
inline std::uniform_int_distribution directions{0, 3};

class Bug {
public:
        virtual ~Bug() = default;


        virtual void display();

        virtual void move() = 0;

        [[nodiscard]] int getId() const;

        [[nodiscard]] pair<int, int> getPosition() const;

        [[nodiscard]] bool getAlive() const;

        void heal();

        [[nodiscard]] int getHealth() const;

        [[nodiscard]] bool getFrozen() const;

        virtual string displayTypeAndID();

        virtual string displayLifeHistory() =0;

        [[nodiscard]] string displayLifeHistoryInitial() const;

        Bug(int id, int x_Coordinate, int y_Coordinate, Direction direction, int health);

        void setFrozen();

        void setNotFrozen();


        void setAlive(bool);

        virtual void takeDamage(int damage);

        void setEatenById(const string &_eatenById);

protected:
        int id{};
        pair<int, int> position;
        Direction direction_{};
        int health{};
        bool alive{true};
        list<pair<int, int> > path;
        string eatenById{};

        [[nodiscard]] bool isWayBlocked() const;

        bool frozen;
};
#endif //A_BUGS_LIFE_BUG_H
