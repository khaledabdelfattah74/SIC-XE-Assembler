//
//  SicParser.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "SicParser.hpp"
#include "SourceCodeTable.hpp"
#include "OpTable.hpp"
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
    OpTable opTable = *new OpTable();
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        istringstream str(line);
        vector<string> fields;
        string field;
        int flag = 0;
        int opIndex = -1;
        bool has_comment = false;
        
        while (str >> field) {
            fields.push_back(field);
            if (field[0] != '.' && !has_comment)
                flag++;
            if (field[0] == '.')
                has_comment = true;
        }
        
        for (int i = 0; i < flag; i ++) {
            if (opTable.found(to_upper(fields[i])))
                opIndex = i;
        }

        Entry entry = *new Entry("", "", "", "", false);
        if (fields[0][0] == '.') {
            entry = *new Entry("", "", "", line, true);
        } else {
            string comment = get_comment(fields, flag);
            switch (flag) {
                case 0:
                    // Error
                    break;
                case 1:
                    entry = *new Entry("", fields[0], "", comment, false);
                    break;
                case 2:
                    if (opIndex == 0)
                        entry = *new Entry("", fields[0], fields[1], comment, false);
                    else
                        entry = *new Entry(fields[0], fields[1], "", comment, false);
                    break;
                case 3:
                    entry = *new Entry(fields[0], fields[1], fields[2], comment, false);
                    break;
                default:
                    // Error
                    string operand = "";
                    for (int i = 2; i < flag; i ++)
                        operand += fields[i] + " ";
                    entry = *new Entry(fields[0], fields[1], operand, comment, false);
                    break;
            }
        }
        sourceCodeTable.addEntry(entry);
    }
    return sourceCodeTable;
}

string SicParser::get_comment(vector<string> strings, int start) {
    string str = "";
    for (int i = start; i < strings.size(); i++)
        str += strings[i] + " ";
    return str;
}

string SicParser::to_upper(string str) {
    string upper_case_string = "";
    for (char c : str)
        upper_case_string += toupper(c);
    return upper_case_string;
}
