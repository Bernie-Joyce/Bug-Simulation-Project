//
// Created by Bernie Joyce on 22/04/2026.
//

#ifndef A_BUGS_LIFE_BOARD_H
#define A_BUGS_LIFE_BOARD_H
#include <vector>

#include "Bug.h"


class Board {
        vector<Bug *> bug_vector;
        vector<vector<Bug *> > boardCells;
        static void parseLine(const string &line, Bug * &bug);
        void fillBoardCells();

public:
        void load(const std::string &fileName);

        Board ();

        void getBugByID() const;

        void displayBoardCells() const;

        void displayAllBugs() const;

        void tap() const;

        void displayAllBugsLifeHistory() const;

        void deleteBugPointers();

        static void printMenuOptions();
};


#endif //A_BUGS_LIFE_BOARD_H
