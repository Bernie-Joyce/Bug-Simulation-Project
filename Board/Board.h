//
// Created by Bernie Joyce on 22/04/2026.
//

#ifndef A_BUGS_LIFE_BOARD_H
#define A_BUGS_LIFE_BOARD_H
#include <map>
#include <vector>

#include "../Bugs/Bug.h"


class Board {
        vector<Bug *> alive_bugs;
        vector<Bug *> all_bugs;
        vector<vector<Bug *> > boardCells;
        vector<Bug *> dead_bugs;
        vector<int> foodIndexes;

        static void parseLine(const string &line, Bug * &bug);
        void fillBoardCells();
        void updateWinnersNumberOfWins();



public:

        void fillBoardWithFood();

        void displayWinHistory();

        void load(const std::string &fileName);

        void writeLifeHistory(const std::string &filename) const;

        Board();

        void menu();

        void getBugByID() const;

        void displayBoardCells() const;

        void displayAllBugs() const;

        void tap();

        void displayAllBugsLifeHistory() const;

        void deleteBugVector();

        static void printMenuOptions();

        void fightingLogic() const;

        void runSimulation();

        void readWinHistory(map<int, int> winTracker);

        void writeWinHistory(map<int, int> winTracker);

        void delete_board_cells();

        ~Board();
};


#endif //A_BUGS_LIFE_BOARD_H
