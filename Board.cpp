#include "Board.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include "Crawler.h"
#include "Hopper.h"

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

Board::Board() {
        this->boardCells.resize(10 * 10);
}

void Board::fillBoardCells() {
        for (int i = 0; i < bug_vector.size(); i++) {
                int width = 10;
                Bug *bug = bug_vector[i];
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
        int length = 10;
        int width = 10;
        for (int x = 0; x < width; x++) {
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

void Board::tap() const {
        if (bug_vector.empty()) cout << "No bugs loaded!" << endl;
        //set frozen bug
        std::uniform_int_distribution<> frozenPicker{0, static_cast<int>(bug_vector.size())};
        int indexOfFrozenBug = frozenPicker(mt);
        bug_vector[indexOfFrozenBug]->setFrozen();
        for (Bug *bug: bug_vector) {
                if (!bug->getFrozen()) {
                        bug->move();
                }
        }
        bug_vector[indexOfFrozenBug]->setNotFrozen();
        //check if bugs are landed on same cell
        const int width = 10;
        int length = 10;
        for (int x = 0; x < width; x++) {
                for (int y = 0; y < length; y++) {
                        if (vector<Bug *> cell = boardCells[x + (y * width)]; cell.size() > 1) {
                        }
                }
        }


        //pair bugs for fighting

        //if uneven number of bugs decide which bug is safe

        //three rounds of fighting where each bug takes between 1 - 5 damage

        //if a bug dies the fight ends

        //check if bugs died
}

void Board::displayAllBugsLifeHistory() const {
        for (Bug *bug: bug_vector) {
                bug->displayLifeHistory();
                cout << endl;
        }
}

void Board::deleteBugPointers() {
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
}
