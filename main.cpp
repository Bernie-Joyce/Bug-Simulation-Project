#include <iostream>
#include <ostream>

#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"

int main() {
        vector<Bug*> bug_vector;
        auto* hopper = new Hopper(101,0,0,west,10,2);
        bug_vector.push_back(hopper);
        auto* crawler = new Crawler(102, 0,8, north,8);
        bug_vector.push_back(crawler);
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
