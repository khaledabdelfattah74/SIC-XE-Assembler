//
//  Pass1.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "Pass1.hpp"
#include <iostream>
#include <cstring>
#include "SicParser.hpp"
#include "SourceCodeTable.hpp"
#include "SymTable.hpp"
#include "OpTable.hpp"
#include <string>
#include <sstream>

using namespace std;
Pass1::Pass1(string path) {
    cout << "Pass1 object created with path" + path<< endl;
    this->path = path.append("o");
    SicParser sicParser;
    this->sourceCodeTable = sicParser.parse(path);
    mainLoop();
}

void Pass1::mainLoop() {
    SymTable symTab;
    OpTable opTable;
    cout << "mainLoop called h" << endl;
    int startingAddress;
    int locctr;
    Entry* currentEntrythis = sourceCodeTable.fetchNextEntry();
    //TODO do not forget to ignore case here
    if (currentEntrythis->getOpCode() == "START") {
        //TODO donont forget to convert the operand to integer
        //startingAddress = currentEntrythis.getOperand();
        locctr = startingAddress;
        //TODO write to intermediate file
        currentEntrythis = sourceCodeTable.fetchNextEntry();
    } else {
        locctr = 0;
    }
    //TODO Ignore case in this comparison
    while (currentEntrythis->getOpCode() != "END") {
        if (!currentEntrythis->isCommentLine()) {
            if(currentEntrythis->getLable().length() != 0) {
                bool repeated = symTab.found(currentEntrythis->getLable());
                if (repeated) {
                    //TODO set Error flag
                } else {
                    symTab.insert(currentEntrythis->getLable(), locctr);
                }
                
            }
            //DO not forget to convert to upper to case
            bool validOpCode = opTable.found(currentEntrythis->getOpCode());
            if (validOpCode) {
                locctr += opTable.lengthOf(currentEntrythis->getOpCode());
                //TODO IGNORE CASE
            } else if (currentEntrythis->getOpCode() == "WORD") {
                locctr += 3;
            } else if (currentEntrythis->getOpCode() == "RESW") {
                //TODO donont forget to convert the operand to integer
                istringstream buffer(currentEntrythis->getOperand());
                int numOfWords;
                buffer >> numOfWords;
                locctr += 3 * numOfWords;
            } else if (currentEntrythis->getOpCode() == "RESB") {
                //TODO donont forget to convert the operand to integer
                istringstream buffer(currentEntrythis->getOperand());
                int numOfBytes;
                buffer >> numOfBytes;
                locctr += numOfBytes;
            } else if (currentEntrythis->getOpCode() == "BYTE") {
                //TODO Implement this function
                locctr += getLengthOf(currentEntrythis->getOperand());
            } else {
                //TODO
                //setError Flag invalid operation code
            }
        }
        //TODO write current line to intermediate file
        currentEntrythis = sourceCodeTable.fetchNextEntry();
    }
    //TODO write current line to intermediate file
    //TODO write to file (loccotr - starting address)
}


int Pass1::getLengthOf(string constant) {
    string value = constant.substr(2, constant.length() - 3);
    int integerValue;
    //TODO Convert Value to integer and store in integer value
    return integerValue;
}

void Pass1::writeCurrenLineToIntermediateFile(string line) {
    ofstream outfile;
    outfile.open(path, ios_base::app);
    outfile << line << endl;
    outfile.close();
}

