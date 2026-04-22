#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Crawler.h"
#include "Hopper.h"

void FileReader::load(const std::string &fileName, vector<Bug *> &bugVector) {
        if (ifstream fin(fileName); fin.is_open()) {
                string line;

                while (getline(fin, line)) {
                        Bug *currentBug = nullptr;
                        parseLine(line, currentBug);
                        if (currentBug != nullptr) {
                                bugVector.push_back(currentBug);
                        }
                }
                fin.close();
        } else {
                cout << "Error opening file." << endl;
        }
}

void FileReader::parseLine(const string &line, Bug *&bug) {
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