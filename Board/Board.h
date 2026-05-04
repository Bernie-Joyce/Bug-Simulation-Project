//
// Created by Bernie Joyce on 22/04/2026.
//

#ifndef A_BUGS_LIFE_BOARD_H
#define A_BUGS_LIFE_BOARD_H
#include <vector>

#include "../Bugs/Bug.h"


class Board {
        vector<Bug *> bug_vector;
        vector<vector<Bug *> > boardCells;

        static void parseLine(const string &line, Bug * &bug);

        void fillBoardCells();

public:
        void load(const std::string &fileName);

        Board();

        void getBugByID() const;

        void displayBoardCells() const;

        void displayAllBugs() const;

        void tap();

        void displayAllBugsLifeHistory() const;

        void deleteBugVector();

        static void printMenuOptions();

        void fightingLogic();

        void runSimulation();

        void delete_board_cells();

        ~Board();
};


#endif //A_BUGS_LIFE_BOARD_H
