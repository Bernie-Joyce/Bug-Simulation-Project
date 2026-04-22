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
        getline(cin, command);

        int commandNumber = stoi(command);

        while (commandNumber != 0) {
                switch (commandNumber) {
                        case 1: FileReader::load("bugs.txt", bug_vector);
                                break;
                        case 2: for (Bug *bug: bug_vector) {
                                        bug->display();
                                        cout << endl;
                                }
                                break;
                        case 3: {
                                cout << "Input bug id" << endl;
                                string bugId;
                                cin.ignore();
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
                                break;
                        }

                        case 4:
                                for (Bug *bug: bug_vector) {
                                        bug->move();
                                }
                                break;
                        default: cout << "Invalid command" << endl;
                }
                        cout << "Enter a new command: ";
                        getline(cin, command);
                        commandNumber = stoi(command);


        }

        for (const Bug *bug: bug_vector) {
                delete bug;
        }
        bug_vector.clear();
        return 0;
}