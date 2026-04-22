#include <iostream>
#include <ostream>

#include "Board.h"
#include "Bug.h"
#include "FileReader.h"

int main() {
        Board board;
        Board::printMenuOptions();
        int commandNumber = 0;
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
                        case 1: board.load("bugs.txt");
                                break;
                        case 2: board.displayAllBugs();
                                break;
                        case 3: try {
                                        board.getBugByID();
                                } catch (const std::exception &) {
                                        cout << "Invalid ID" << endl;
                                }
                                break;
                        case 4: board.tap();
                                break;
                        case 5: board.displayAllBugsLifeHistory();
                                break;
                        case 6:
                                cout << "\nDisplay all cells";
                                break;
                        case 7:
                                cout << "\nRun simulation";
                                break;
                        case 8:
                                cout << "Program over";
                                break;
                        default: cout << "Invalid command" << endl;
                }
        }
       board.deleteBugPointers();
        return 0;
}
