/*
 * SicParser.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#include "SicParser.h"
#include "SourceCodeTable.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
SicParser::SicParser() {
}

SicParser::~SicParser() {
    // TODO Auto-generated destructor stub
}


//TODO IMPORTATNT if a field in an entry is not exist insert it as a string with length zero
//TODO parsing code goes here to fill and return a source code table object with entries.
SourceCodeTable parse(string path) {
    SourceCodeTable sourceCodeTable = *new SourceCodeTable();
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        istringstream str(line);
        vector<string> fields;
        string field;
        while (str >> field) {
            fields.push_back(field);
        }
        
        Entry entry = *new Entry("", "", "", "", false);
        if (fields[0][0] == '.') {
            entry = *new Entry("", "", "", line, true);
        } else {
            switch (fields.size()) {
                case 2:
                    entry = *new Entry("", fields[0], fields[1], "", false);
                    break;
                case 3:
                    if (fields[2][0] == '.') {
                        entry = *new Entry("", fields[0], fields[1], fields[2], false);
                    } else {
                        entry = *new Entry(fields[0], fields[1], fields[2], "", false);
                    }
                    break;
                case 4:
                    entry = *new Entry(fields[0], fields[1], fields[2], fields[4], false);
                    break;
                default:
                    // Error
                    break;
            }
        }
        sourceCodeTable.addEntry(entry);
    }
    return sourceCodeTable;
}
