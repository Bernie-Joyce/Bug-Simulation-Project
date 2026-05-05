#include "Board.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <thread>

#include "../Bugs/Crawler.h"
#include "../Bugs/Hopper.h"
#include "../Bugs/Tank.h"

void Board::load(const std::string &fileName) {
        if (!bug_vector.empty()) {
                cout << "Bugs already loaded" << endl;
        } else {
                if (ifstream fin(fileName); fin.is_open()) {
                        string line;

                        while (getline(fin, line)) {
                                Bug *currentBug = nullptr;
                                parseLine(line, currentBug);
                                if (currentBug != nullptr) {
                                        bug_vector.push_back(currentBug);
                                }
                        }
                        fin.close();
                        fillBoardCells();
                        cout << "Bugs Loaded: " << bug_vector.size() << endl;
                } else {
                        cout << "Error opening file." << endl;
                }
        }
}

void Board::writeLifeHistory(const std::string &filename) {

}

Board::Board() {
        this->boardCells.resize(10 * 10);
}

void Board::fillBoardCells() {
        for (auto bug: bug_vector) {
                constexpr int width = 10;
                pair position = bug->getPosition();
                vector<Bug *> &cell = boardCells[position.first + (position.second * width)];
                cell.push_back(bug);
        }
}

void Board::getBugByID() const {
        if (bug_vector.empty()) {
                cout << "No bugs loaded!" << endl;
                return;
        }
        cout << "Input bug id" << endl;
        string bugId;
        getline(cin, bugId);
        const int bugIdNum = stoi(bugId);
        bool found = false;
        for (Bug *bug: bug_vector) {
                if (bug->getId() == bugIdNum) {
                        bug->display();
                        cout << endl;
                        found = true;
                }
        }
        if (!found) {
                cout << "bug not found" << endl;
        }
}

void Board::displayBoardCells() const {
        int width = 10;
        for (int x = 0; x < width; x++) {
                constexpr int length = 10;
                for (int y = 0; y < length; y++) {
                        vector<Bug *> cell = boardCells[x + (y * width)];
                        cout << "(" << x << "," << y << "): ";
                        if (cell.empty()) {
                                cout << "empty";
                        } else {
                                for (int i = 0; i < cell.size(); i++) {
                                        Bug *bug = cell[i];
                                        bug->displayTypeAndID();
                                        if (cell.size() > 1 && i < cell.size() - 1) {
                                                cout << ",";
                                        }
                                }
                        }
                        cout << endl;
                }
        }
}

void Board::displayAllBugs() const {
        if (bug_vector.empty()) cout << "No bugs loaded!" << endl;
        for (Bug *bug: bug_vector) {
                bug->display();
                cout << endl;
        }
}

void Board::tap() {
        if (bug_vector.empty()) {
                cout << "No bugs loaded!" << endl;
        } else {
                //set frozen bug
                std::uniform_int_distribution<> frozenPicker{0, static_cast<int>(bug_vector.size() - 1)};
                int indexOfFrozenBug = frozenPicker(mt);
                bug_vector[indexOfFrozenBug]->setFrozen();
                for (Bug *bug: bug_vector) {
                        if (!bug->getFrozen()) {
                                bug->move();
                        }
                }
                bug_vector[indexOfFrozenBug]->setNotFrozen();
                fightingLogic();

                for (Bug *bug: bug_vector) {
                        if (!bug->getAlive()) {
                                dead_bugs.push_back(bug);
                        }
                }
                std::erase_if(bug_vector, [](Bug *bug) {
                        if (!bug->getAlive()) {
                                return true;
                        }
                        return false;
                });
                for (auto &cell: boardCells) {
                        cell.clear();
                }
                fillBoardCells();
        }
}

void Board::displayAllBugsLifeHistory() const {
        for (Bug *bug: bug_vector) {
                bug->displayLifeHistory();
                cout << endl;
        }
}

void Board::deleteBugVector() {
        for (const Bug *bug: bug_vector) {
                delete bug;
        }
        bug_vector.clear();
}

void Board::printMenuOptions() {
        cout << "1. Initialize Bug Board (load data from file)" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug (given an id)" << endl;
        cout << "4. Tap the Bug Board (causes move all, then fight/eat)" << endl;
        cout << "5. Display Life History of all Bugs (path taken)" << endl;
        cout << "6. Display all Cells listing their Bugs" << endl;
        cout << "7. Run simulation (generates a Tap every second)" << endl;
        cout << "8. Exit (write Life History of all Bugs to file)" << endl;
}

void Board::fightingLogic() {
        //check if bugs are landed on same cell
        constexpr int width = 10;
        std::uniform_int_distribution<> damagePicker{1, 5};
        for (int x = 0; x < width; x++) {
                int length = 10;
                for (int y = 0; y < length; y++) {
                        if (vector<Bug *> cell = boardCells[x + (y * width)]; cell.size() > 1) {
                                std::uniform_int_distribution<> cellPicker{0, static_cast<int>(cell.size() - 1)};
                                int indexOfSafeBug = cellPicker(mt);
                                //if uneven number of bugs decide which bug is safe
                                auto eligibleFighters = cell;
                                if (cell.size() % 2 == 1) {
                                        eligibleFighters.erase(eligibleFighters.begin() + indexOfSafeBug);
                                }
                                //pair bugs for fighting
                                vector<pair<Bug *, Bug *> > pairedBugs;
                                for (int i = 0; i < eligibleFighters.size() - 1; i += 2) {
                                        auto fight = make_pair(eligibleFighters[i], eligibleFighters[i + 1]);
                                        pairedBugs.push_back(fight);
                                }
                                //three rounds of fighting where each bug takes between 1 - 5 damage
                                for (const auto &pairedBug: pairedBugs) {
                                        for (int round = 0; round < 3; round++) {
                                                if (pairedBug.first->getAlive() && pairedBug.second->getAlive()) {
                                                        int firstDamage = damagePicker(mt);
                                                        pairedBug.first->takeDamage(firstDamage);
                                                        int secondDamage = damagePicker(mt);
                                                        pairedBug.second->takeDamage(secondDamage);
                                                        if (pairedBug.first->getHealth() < 1) {
                                                                pairedBug.first->setAlive(false);
                                                        }
                                                        if (pairedBug.second->getHealth() < 1) {
                                                                pairedBug.second->setAlive(false);
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
}

void Board::runSimulation() {
        while (bug_vector.size() > 1) {
                //this_thread::sleep_for(chrono::seconds(1));
                tap();
        }
}


void Board::delete_board_cells() {
        for (auto &boardCell: boardCells) {
                boardCell.clear();
        }
}

Board::~Board() {
        delete_board_cells();
        deleteBugVector();
}


void Board::parseLine(const string &line, Bug *&bug) {
        stringstream ss(line);
        string type, id, x_Coord, y_Coord, direction, health;
        getline(ss, type, ';');
        getline(ss, id, ';');
        getline(ss, x_Coord, ';');
        getline(ss, y_Coord, ';');
        getline(ss, direction, ';');
        getline(ss, health, ';');
        auto enumDirection = static_cast<Direction>(stoi(direction));

        if (type == "C") {
                bug = new Crawler(stoi(id), stoi(x_Coord), stoi(y_Coord), enumDirection, stoi(health));
        }

        if (type == "H") {
                string hopLength;
                getline(ss, hopLength, ';');
                bug = new Hopper(stoi(id), stoi(x_Coord), stoi(y_Coord), enumDirection, stoi(health),
                                 stoi(hopLength));
        }

        if (type == "T") {
                string defense;
                getline(ss, defense, ';');
                bug = new Tank(stoi(id), stoi(x_Coord), stoi(y_Coord), enumDirection, stoi(health),
                               stoi(defense));
        }
}
