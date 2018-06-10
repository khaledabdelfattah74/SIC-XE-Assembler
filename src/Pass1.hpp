//
//  Pass1.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//


#ifndef Pass1_hpp
#define Pass1_hpp
#include <stdio.h>
#include "SymTable.hpp"
#include "SourceCodeTable.hpp"
#include <fstream>
#include "LitTab.h"
using namespace std;

class Pass1 {
public:
    Pass1(string path);
    void mainLoop();
    string outPath;
    string symTablePath;
    bool error;
    int programLength;
    LitTab litTab;
    int getNumOfErrors();
private:
    int numOfErrors = 0;
    bool baseAvailable = false;
    int base = 0;
    SourceCodeTable sourceCodeTable;
    int getLengthOf(std::string);
    void writeCurrenLineToIntermediateFile(int ,int , int, Entry);
    string to_upper(string str);
    void printSymTable(SymTable);
    void printLitTable(LitTab litTable);
    int valueOfExpression(string, SymTable);
    const vector<string> explode(const string&, const char&, const char&);
    bool is_number(const std::string&);
};

#endif /* Pass1_hpp */
