#include <iostream>
#include <ostream>
#include "Bug.h"
#include "FileReader.h"

int main() {
        vector<Bug *> bug_vector;
        cout << "1. Initialize Bug Board (load data from file)" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug (given an id)" << endl;
        cout << "4. Tap the Bug Board (causes move all, then fight/eat)" << endl;
        cout << "5. Display Life History of all Bugs (path taken)" << endl;
        cout << "6. Display all Cells listing their Bugs" << endl;
        cout << "7. Run simulation (generates a Tap every second)" << endl;
        cout << "8. Exit (write Life History of all Bugs to file)" << endl;
        string command;


        int commandNumber = 0;

        while (commandNumber != 8) {
                cout << "Enter a command (1 - 8): ";
                getline(cin, command);
                try {
                        commandNumber = stoi(command);
                } catch (const std::exception &) {
                        cout << "Please enter a valid number." << endl;
                        continue;
                }

                switch (commandNumber) {
                        case 1:
                                if (bug_vector.empty()) {
                                        FileReader::load("bugs.txt", bug_vector);
                                        cout << "Bugs Loaded: " << bug_vector.size() << endl;
                                } else {
                                        cout << "Bugs already loaded" << endl;
                                }
                                break;
                        case 2: if (bug_vector.empty()) cout << "No bugs loaded!" << endl;
                                for (Bug *bug: bug_vector) {
                                        bug->display();
                                        cout << endl;
                                }
                                break;
                        case 3: {
                                try {
                                        if (bug_vector.empty()) {
                                                cout << "No bugs loaded!" << endl;
                                                continue;
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
                                } catch (const std::exception &) {
                                        cout << "Invalid ID" << endl;
                                }
                                break;
                        }
                        case 4:
                                for (Bug *bug: bug_vector) {
                                        bug->move();
                                }
                                break;
                        case 5: for (Bug *bug: bug_vector) {
                                        bug->displayLifeHistory();
                                        cout << endl;
                                }
                                break;
                        case 6:
                                cout << "Display all cells";
                                break;
                        case 7:
                                cout << "Run simulation";
                                break;
                        case 8:
                                cout << "Program over";
                                break;
                        default: cout << "Invalid command" << endl;
                }
        }

        for (const Bug *bug: bug_vector) {
                delete bug;
        }
        bug_vector.clear();
        return 0;
}
