//
//  SicParser.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "SicParser.hpp"
#include "SourceCodeTable.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
SicParser::SicParser() {
}

SicParser::~SicParser() {
}


SourceCodeTable SicParser::parse(string path) {
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
