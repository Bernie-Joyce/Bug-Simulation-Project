#include <iostream>
#include <ostream>
#include "Bug.h"
#include "FileReader.h"

int main() {
        vector<Bug*> bug_vector;
        FileReader::load("bugs.txt",bug_vector);
        for (Bug* bug: bug_vector) {
                bug->display();
                cout << endl;
        }

        for (Bug* bug: bug_vector) {
                bug->move();
                cout << endl;
        }
        for (Bug* bug: bug_vector) {
                bug->display();
                cout << endl;
        }

        for (const Bug* bug: bug_vector) {
               delete bug;
        }
        bug_vector.clear();
        return 0;
}
