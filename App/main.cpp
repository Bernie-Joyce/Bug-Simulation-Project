#include <iostream>
#include <ostream>

#include "../Board/Board.h"
#include "../Bugs/Bug.h"

int main() {
        Board board = Board{};
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
                        case 3: board.getBugByID();
                                break;
                        case 4: board.tap();
                                break;
                        case 5: board.displayAllBugsLifeHistory();
                                break;
                        case 6:
                                board.displayBoardCells();
                                break;
                        case 7:
                                board.runSimulation();
                                break;
                        case 8:
                                board.writeLifeHistory("bugs_life_history_date_time.out");
                                break;
                        default: cout << "Invalid command" << endl;
                }
        }
        board.deleteBugVector();
        return 0;
}
