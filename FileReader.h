//
// Created by Bernie Joyce on 22/04/2026.
//

#ifndef A_BUGS_LIFE_FILEREADER_H
#define A_BUGS_LIFE_FILEREADER_H
#include <string>

#include "Bug.h"


class FileReader {
public:
        static void load(const std::string& fileName, vector<Bug*> &bugVector);
        static void parseLine(const string& line, Bug* &bug);
};


#endif //A_BUGS_LIFE_FILEREADER_H