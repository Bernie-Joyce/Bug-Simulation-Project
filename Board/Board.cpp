#include "Board.h"
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <thread>

#include "../Bugs/Crawler.h"
#include "../Bugs/Hopper.h"
#include "../Bugs/Tank.h"

void Board::load(const std::string &fileName) {
        if (!alive_bugs.empty()) {
                cout << "Bugs already loaded" << endl;
        } else {
                if (ifstream fin(fileName); fin.is_open()) {
                        string line;

                        while (getline(fin, line)) {
                                Bug *currentBug = nullptr;
                                parseLine(line, currentBug);
                                if (currentBug != nullptr) {
                                        alive_bugs.push_back(currentBug);
                                        all_bugs.push_back(currentBug);
                                }
                        }
                        fin.close();
                        fillBoardCells();
                        fillBoardWithFood();
                        cout << "Bugs Loaded: " << alive_bugs.size() << endl;
                } else {
                        cout << "Error opening file." << endl;
                }
        }
}

void Board::writeLifeHistory(const std::string &filename) const {
        if (ofstream writer(filename); writer.is_open()) {
                for (Bug *bug: all_bugs) {
                        writer << bug->displayLifeHistory() << endl;
                }
        }
}

Board::Board() {
        this->boardCells.resize(10 * 10);
}

void Board::fillBoardCells() {
        for (auto bug: alive_bugs) {
                constexpr int width = 10;
                pair position = bug->getPosition();
                vector<Bug *> &cell = boardCells[position.first + (position.second * width)];
                cell.push_back(bug);
        }
}

void Board::fillBoardWithFood() {
        std::uniform_int_distribution<> foodPicker{0, 99};
        while (foodIndexes.size() != 10) {
                foodIndexes.push_back(foodPicker(mt));
        }
}

void Board::getBugByID() const {
        if (alive_bugs.empty()) {
                cout << "No bugs loaded!" << endl;
                return;
        }
        cout << "Input bug id" << endl;
        string bugId;
        getline(cin, bugId);
        const int bugIdNum = stoi(bugId);
        bool found = false;
        for (Bug *bug: alive_bugs) {
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
        const int width = 10;
        const int length = 10;
        const int cellWidth = 20;

        cout << string(width * (cellWidth + 3) + 1, '-') << endl;

        for (int y = 0; y < length; y++) {
                cout << "|";
                for (int x = 0; x < width; x++) {
                        const vector<Bug *> &cell = boardCells[x + (y * width)];

                        bool hasFood = std::ranges::find(foodIndexes, x + (y * width)) != foodIndexes.end();

                        string cellText;
                        if (cell.empty()) {
                                cellText = hasFood ? "(FOOD)" : ".";
                        } else {
                                for (size_t i = 0; i < cell.size(); i++) {
                                        cellText += cell[i]->displayTypeAndID();
                                        if (i < cell.size() - 1) cellText += ",";
                                }
                        }
                        printf(" %-*s |", cellWidth, cellText.substr(0, cellWidth).c_str());
                }
                cout << endl;
                cout << string(width * (cellWidth + 3) + 1, '-') << endl;
        }
}

void Board::displayAllBugs() const {
        if (all_bugs.empty()) cout << "No bugs loaded!" << endl;
        for (Bug *bug: all_bugs) {
                bug->display();
                cout << endl;
        }
}

void Board::menu() {
        printMenuOptions();
        int commandNumber = 0;
        string bug_file = "bugs.txt";
        string bug_history_file = "bugs_life_history_date_time.out";
        while (commandNumber != 8) {
                cout << "Enter a command (1 - 8): ";
                string command;
                getline(cin, command);
                try {
                        commandNumber = stoi(command);
                } catch (const std::exception &) {
                        cout << "Please enter a valid number." << endl;
                        continue;
                }
                switch (commandNumber) {
                        case 1: load(bug_file);
                                break;
                        case 2: displayAllBugs();
                                break;
                        case 3: getBugByID();
                                break;
                        case 4: tap();
                                break;
                        case 5: displayAllBugsLifeHistory();
                                break;
                        case 6: displayBoardCells();
                                break;
                        case 7: runSimulation();
                                break;
                        case 8: writeLifeHistory(bug_history_file);
                                break;
                        default: cout << "Invalid command" << endl;
                }
        }
        deleteBugVector();
}

void Board::tap() {
        if (alive_bugs.empty()) {
                cout << "No bugs loaded!" << endl;
        } else {
                //set frozen bug
                std::uniform_int_distribution<> frozenPicker{0, static_cast<int>(alive_bugs.size() - 1)};
                int indexOfFrozenBug = frozenPicker(mt);
                alive_bugs[indexOfFrozenBug]->setFrozen();
                for (Bug *bug: alive_bugs) {
                        if (!bug->getFrozen()) {
                                bug->move();
                        }
                        int foodIndex = bug->getPosition().first + (bug->getPosition().second * 10);
                        if (std::ranges::find(foodIndexes, foodIndex) != foodIndexes.end()) {
                                bug->heal();
                                std::erase(foodIndexes, foodIndex);
                        }
                }
                alive_bugs[indexOfFrozenBug]->setNotFrozen();
                for (auto &cell: boardCells) {
                        cell.clear();
                }
                fillBoardCells();

                fightingLogic();


                std::erase_if(alive_bugs, [this](Bug *bug) {
                        if (!bug->getAlive()) {
                                dead_bugs.push_back(bug);
                                return true;
                        }
                        return false;
                });
        }
}

void Board::displayAllBugsLifeHistory() const {
        for (Bug *bug: all_bugs) {
                cout << bug->displayLifeHistory() << endl;
        }
}

void Board::deleteBugVector() {
        for (const Bug *bug: all_bugs) {
                delete bug;
        }
        all_bugs.clear();
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

void Board::fightingLogic() const {
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
                                                                pairedBug.first->setEatenById(
                                                                        to_string(pairedBug.second->getId()));
                                                        }
                                                        if (pairedBug.second->getHealth() < 1) {
                                                                pairedBug.second->setAlive(false);
                                                                pairedBug.second->setEatenById(
                                                                        to_string(pairedBug.first->getId()));
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
}

void Board::runSimulation() {
        int counter = 0;
        while (alive_bugs.size() > 1) {
                tap();
                system("clear");
                cout.flush();
                cout << "Round: " << to_string(++counter) << endl;
                displayBoardCells();
                std::cout << std::flush;
              //  this_thread::sleep_for(chrono::seconds(1));
        }

                cout << "Winner: " << alive_bugs[0]->displayTypeAndID() << endl;

        updateWinnersNumberOfWins();
}

void Board::readWinHistory(map<int, int> winTracker) {
        ifstream reader("winners.txt");

        if (reader.is_open()) {
                string line;
                while (getline(reader, line)) {
                        if (line.empty()) continue;
                        stringstream ss(line);
                        string idStr, winStr;

                        getline(ss, idStr, ';');
                        getline(ss, winStr, ';');

                        winTracker[stoi(idStr)] = stoi(winStr);
                }
                reader.close();
        }
}

void Board::writeWinHistory(map<int, int> winTracker) {
        ofstream writer("winners.txt");

        if (writer.is_open()) {
                for (auto const& [id, wins] : winTracker) {
                        writer << id << ";" << wins << ";" << std::endl;
                }
                writer.close();
        }
}

void Board::updateWinnersNumberOfWins() {
        int winnersId = alive_bugs[0]->getId();
        map<int, int> winTracker;
        readWinHistory(winTracker);
        winTracker[winnersId]++;
        writeWinHistory(winTracker);
}

void Board::displayWinHistory() {

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
