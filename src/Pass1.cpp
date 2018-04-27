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
#include <stdio.h>

using namespace std;
Pass1::Pass1(string path) {
    this->outPath.append(path, 0, path.length() - 4);
    this->outPath.append("Out.txt");
    remove(outPath.c_str());
    SicParser sicParser = * new SicParser();
    this->sourceCodeTable = sicParser.parse(path);
    this->error = false;
    mainLoop();
}

void Pass1::mainLoop() {
    SymTable symTab;
    OpTable opTable;
    int startingAddress = 0;
    int locctr = 0;
    int lineNo = 0;
    Entry currentEntry = *sourceCodeTable.fetchNextEntry();
    writeCurrenLineToIntermediateFile(lineNo, locctr, 0, currentEntry);
    lineNo++;
    //TODO do not forget to ignore case here
    if (currentEntry.getOpCode() == "START") {
        istringstream buffer(currentEntry.getOperand());
        buffer >> startingAddress;
        locctr = startingAddress;
        stringstream stream;
        stream << locctr;
        stream >> hex >> locctr;
        stream << startingAddress;
        stream >> hex >> startingAddress;
        writeCurrenLineToIntermediateFile(lineNo, locctr, 0, currentEntry);
        lineNo++;
        currentEntry = *sourceCodeTable.fetchNextEntry();
    } else {
        locctr = 0;
        startingAddress = 0;
    }
    //TODO Ignore case in this comparison
    int currentInstructionLength = 0;
    while (currentEntry.getOpCode() != "END") {
        if (!currentEntry.isCommentLine()) {
            if(currentEntry.getLable().length() != 0) {
                bool repeated = symTab.found(currentEntry.getLable());
                if (repeated) {
                    this->error = true;
                    writeCurrenLineToIntermediateFile(-1, locctr, currentInstructionLength, currentEntry);
                } else {
                    symTab.insert(currentEntry.getLable(), locctr);
                }
            }
            //TODO DO not forget to convert to upper to case
            bool validOpCode = opTable.found(currentEntry.getOpCode());
            if (validOpCode) {
                currentInstructionLength = opTable.lengthOf(currentEntry.getOpCode());
                locctr += currentInstructionLength;
                //TODO IGNORE CASE
            } else if (currentEntry.getOpCode() == "WORD") {
                currentInstructionLength = 3;
                locctr += currentInstructionLength;
            } else if (currentEntry.getOpCode() == "RESW") {
                istringstream buffer(currentEntry.getOperand());
                int numOfWords;
                buffer >> numOfWords;
                currentInstructionLength = 3 * numOfWords;
                locctr += currentInstructionLength;
            } else if (currentEntry.getOpCode() == "RESB") {
                istringstream buffer(currentEntry.getOperand());
                int numOfBytes;
                buffer >> numOfBytes;
                currentInstructionLength = numOfBytes;
                locctr += currentInstructionLength;
            } else if (currentEntry.getOpCode() == "BYTE") {
                currentInstructionLength = getLengthOf(currentEntry.getOperand());
                locctr += currentInstructionLength;
            } else {
                this->error = true;
                writeCurrenLineToIntermediateFile(-2, locctr, currentInstructionLength, currentEntry);
            }
        }
        writeCurrenLineToIntermediateFile(lineNo, locctr, currentInstructionLength, currentEntry);
        lineNo++;
        currentEntry = *sourceCodeTable.fetchNextEntry();
    }
    writeCurrenLineToIntermediateFile(lineNo, locctr, 0, currentEntry);
    lineNo++;
    this->programLength = locctr - startingAddress;
}


int Pass1::getLengthOf(string constant) {
    string value = constant.substr(2, constant.length() - 3);
    int integerValue;
    istringstream buffer(value);
    buffer >> integerValue;
    return integerValue;
}

void Pass1::writeCurrenLineToIntermediateFile(int lineNumber, int locationCounter, int lenOfCurrentInstruction, Entry currentEntry) {
    if (lineNumber == 0) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "Line no.\tAddress   \tLabel   \t\tMnemonic\t\tOperands          \tComments\n"
                                          "\t\t\t\t\t\t\t\t\t\tOp-code" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -1) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "***Duplicate lable definition***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -2) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "***Wrong operand prefix***" << endl;
        outfile.close();
        return;
    }
    string fixedLable = currentEntry.getLable();
    int length = fixedLable.length();
    if (length < 8) {
            for (int i = 0; i < 8 - length; i++) {
                fixedLable.append(" ");
            }
    }
    string fixedOpcode = currentEntry.getOpCode();
    length = fixedOpcode.length();
    if (length < 9) {
        for (int i = 0; i < 9 - length; i++) {
            fixedOpcode.append(" ");
        }
    }
    string fixedOperand = currentEntry.getOperand();
    length = fixedOperand.length();
    if (length < 17) {
        for (int i = 0; i < 17 - length; i++) {
            fixedOperand.append(" ");
        }
    }
    char stro[100];
    sprintf(stro, "%-8d\t%06x\t\t%.8s\t\t%.8s\t\t%.18s\t%s",
        lineNumber,(locationCounter - lenOfCurrentInstruction),
        fixedLable.c_str(),
        fixedOpcode.c_str(),
        fixedOperand.c_str(),
        currentEntry.getComment().c_str());
    ofstream outfile;
    outfile.open(outPath, ios_base::app);
    outfile << stro << endl;
    outfile.close();
    delete stro;
}

