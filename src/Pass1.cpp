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
#include <ctype.h>
#include <regex>
#include "Validator.hpp"
#include "Utilities.h"


using namespace std;
Pass1::Pass1(string path) {
    this->outPath.append(path, 0, path.length() - 4);
    this->symTablePath = this->outPath;
    this->symTablePath.append("SymTable.txt");
    this->outPath.append("Out.txt");
    remove(outPath.c_str());
    remove(symTablePath.c_str());
    SicParser sicParser = * new SicParser();
    this->sourceCodeTable = sicParser.parse(path);
    this->error = false;
    mainLoop();
}

int Pass1::getNumOfErrors() {
    return this->numOfErrors;
}

void Pass1::mainLoop() {
    Utilities utilities;
    SymTable symTab;
    OpTable opTable;
    int startingAddress = 0;
    int locctr = 0;
    int lineNo = 0;
    Entry currentEntry = sourceCodeTable.fetchNextEntry();
    writeCurrenLineToIntermediateFile(lineNo, locctr, 0, currentEntry);
    lineNo++;


    while (currentEntry.isCommentLine()) {
        writeCurrenLineToIntermediateFile(lineNo, locctr, 0, currentEntry);
        lineNo++;
        currentEntry = sourceCodeTable.fetchNextEntry();
    }



    if (to_upper(currentEntry.getOpCode()) == "START") {
        locctr = utilities.hexToDecimal(currentEntry.getOperand());
        startingAddress = utilities.hexToDecimal(currentEntry.getOperand());
        writeCurrenLineToIntermediateFile(lineNo, locctr, 0, currentEntry);
        lineNo++;
        currentEntry = sourceCodeTable.fetchNextEntry();
    } else {
        locctr = 0;
        startingAddress = 0;
    }

    int currentInstructionLength = 0;
    while (sourceCodeTable.size() != 0 && to_upper(currentEntry.getOpCode()) != "END") {
        //this print is just necessary, I have no idea why!, with out it garbage values appears from under the ground to eat the zombies faces.
        if (!currentEntry.isCommentLine()) {
            if(currentEntry.getLable().length() != 0 && to_upper(currentEntry.getOpCode()) != "EQU") {
                bool repeated = symTab.found(to_upper(currentEntry.getLable()));
                if (repeated) {
                    this->error = true;
                    writeCurrenLineToIntermediateFile(-1, locctr, currentInstructionLength, currentEntry);
                } else if (opTable.found(to_upper(currentEntry.getLable()))) {
                    this->error = true;
                    writeCurrenLineToIntermediateFile(-3, locctr, currentInstructionLength, currentEntry);
                } else if (currentEntry.getLable().c_str()[0] < '0' || currentEntry.getLable().c_str()[0] > '9'){
                    symTab.insert(to_upper(currentEntry.getLable()), locctr);
                } else {
                    this->error = true;
                    writeCurrenLineToIntermediateFile(-3, locctr, currentInstructionLength, currentEntry);
                }
            }
            bool validOpCode = opTable.found(to_upper(currentEntry.getOpCode()));
            if (validOpCode) {
                Validator validator;
                bool valid = validator.check_vaidity(to_upper(currentEntry.getOpCode()), to_upper(currentEntry.getOperand()));
                if (valid) {
                    currentInstructionLength = opTable.lengthOf(to_upper(currentEntry.getOpCode()));
                    locctr += currentInstructionLength;
                } else {
                    writeCurrenLineToIntermediateFile(-10, locctr, currentInstructionLength, currentEntry);
                    this->error = true;
                }
            } else if (to_upper(currentEntry.getOpCode()) == "WORD") {
                currentInstructionLength = 3;
                locctr += currentInstructionLength;
            } else if (to_upper(currentEntry.getOpCode()) == "RESW") {
                istringstream buffer(currentEntry.getOperand());
                int numOfWords = 0;
                buffer >> numOfWords;
                currentInstructionLength = 3 * numOfWords;
                locctr += currentInstructionLength;
            } else if (to_upper(currentEntry.getOpCode()) == "RESB") {
                istringstream buffer(currentEntry.getOperand());
                int numOfBytes = 0;
                buffer >> numOfBytes;
                currentInstructionLength = numOfBytes;
                locctr += currentInstructionLength;
            } else if (to_upper(currentEntry.getOpCode()) == "BYTE") {
                currentInstructionLength = getLengthOf(currentEntry.getOperand());
                if (currentInstructionLength == -1) {
                    writeCurrenLineToIntermediateFile(-10, locctr, currentInstructionLength, currentEntry);
                    this->error = true;
                } else {
                    locctr += currentInstructionLength;
                }
            } else if (to_upper(currentEntry.getOpCode()) == "EQU") {
                int valueOfExp = valueOfExpression(currentEntry.getOperand(), symTab);
                if (valueOfExp == -1) {
                    writeCurrenLineToIntermediateFile(-5, locctr, currentInstructionLength, currentEntry);
                    this->error = true;
                } else if (valueOfExp == -2) {
                    writeCurrenLineToIntermediateFile(-4, locctr, currentInstructionLength, currentEntry);
                    this->error = true;
                } else {
                    symTab.insert(to_upper(currentEntry.getLable()), valueOfExp);
                }
                currentInstructionLength = 0;
                currentEntry = * new Entry(currentEntry.getLable(), "RESW", "NONE", ".Assumption", false);
                lineNo++;
                writeCurrenLineToIntermediateFile(lineNo, valueOfExp, currentInstructionLength, currentEntry);
            } else if (to_upper(currentEntry.getOpCode()) == "ORG") {
                if (currentEntry.getLable() == "") {
                    int valueOfExp = valueOfExpression(currentEntry.getOperand(), symTab);
                    if (valueOfExp == -1) {
                        writeCurrenLineToIntermediateFile(-5, locctr, currentInstructionLength, currentEntry);
                        this->error = true;
                    } else if (valueOfExp == -2) {
                        writeCurrenLineToIntermediateFile(-4, locctr, currentInstructionLength, currentEntry);
                        this->error = true;
                    } else {
                        locctr = valueOfExp;
                    }
                    currentInstructionLength = 0;
                } else {
                    writeCurrenLineToIntermediateFile(-6, locctr, currentInstructionLength, currentEntry);
                    this->error = true;
                }
            } else if (to_upper(currentEntry.getOpCode()) == "BASE") {
                if (currentEntry.getLable() == "") {
                    int valueOfExp = valueOfExpression(currentEntry.getOperand(), symTab);
                    if (valueOfExp == -1) {
                        writeCurrenLineToIntermediateFile(-5, locctr, currentInstructionLength, currentEntry);
                        this->error = true;
                    } else {
                        this->baseAvailable = true;
                        this->base = valueOfExp;
                    }
                    currentInstructionLength = 0;
                } else {
                    writeCurrenLineToIntermediateFile(-6, locctr, currentInstructionLength, currentEntry);
                    this->error = true;
                }
            } else if (to_upper(currentEntry.getOpCode()) == "NOBASE") {
                if (currentEntry.getLable() == "") {
                    if (currentEntry.getOperand() == "") {
                        this->baseAvailable = true;
                        this->base = 0;
                        currentInstructionLength = 0;
                    } else {
                        writeCurrenLineToIntermediateFile(-7, locctr, currentInstructionLength, currentEntry);
                        this->error = true;
                    }
                } else {
                    writeCurrenLineToIntermediateFile(-6, locctr, currentInstructionLength, currentEntry);
                    this->error = true;
                }
            } else if (to_upper(currentEntry.getOpCode()) == "LTORG") {
                if (currentEntry.getLable() == "") {
                    if (currentEntry.getOperand() == "") {
                        locctr = litTab.assignCurrentLiterals(locctr, lineNo, outPath);
                    } else {
                        writeCurrenLineToIntermediateFile(-7, locctr, currentInstructionLength, currentEntry);
                        this->error = true;
                    }
                } else {
                    writeCurrenLineToIntermediateFile(-6, locctr, currentInstructionLength, currentEntry);
                    this->error = true;
                }
            } else {
                this->error = true;
                writeCurrenLineToIntermediateFile(-2, locctr, currentInstructionLength, currentEntry);
            }
            if(currentEntry.getOperand().length() != 0) {
                if (currentEntry.getOperand().c_str()[0] == '=') {
                    if (currentEntry.getOperand().c_str()[2] == '\''
                        && currentEntry.getOperand().c_str()[currentEntry.getOperand().length() - 1] == '\'') {
                        string temp = to_upper(currentEntry.getOperand().substr(0, 2));
                        temp.append(currentEntry.getOperand().substr(2, currentEntry.getOperand().length() - 2));
                        currentEntry.setOperand(temp);
                        bool valid = this->litTab.insert(currentEntry.getOperand());
                        if (!valid) {
                            this->error = true;
                            writeCurrenLineToIntermediateFile(-9, locctr, currentInstructionLength, currentEntry);
                        }
                    }
                }
            }
        }

        if (to_upper(currentEntry.getOpCode()) != "LTORG" && to_upper(currentEntry.getOpCode()) != "ORG" && to_upper(currentEntry.getOperand()) != "NONE" && to_upper(currentEntry.getComment()) != ".Assumption") {
            writeCurrenLineToIntermediateFile(lineNo, locctr, currentInstructionLength, currentEntry);
            lineNo++;
        }
        currentEntry = sourceCodeTable.fetchNextEntry();
    }

    if (this->to_upper(currentEntry.getOpCode()) == "END") {
        if (currentEntry.getLable() == "") {
            this->printSymTable(symTab);
            locctr = litTab.assignCurrentLiterals(locctr, lineNo, outPath);
            this->printLitTable(litTab);
            writeCurrenLineToIntermediateFile(lineNo, locctr, 0, currentEntry);
            lineNo++;
            this->programLength = locctr - startingAddress;
        } else {
            writeCurrenLineToIntermediateFile(-6, locctr, currentInstructionLength, currentEntry);
            this->error = true;
        }
        if (sourceCodeTable.size() != 0) {
            writeCurrenLineToIntermediateFile(-11, locctr, currentInstructionLength, currentEntry);
            this->error = true;
        }
    } else {
        writeCurrenLineToIntermediateFile(lineNo, locctr, 0, currentEntry);
        lineNo++;
        writeCurrenLineToIntermediateFile(-8, locctr, 0, currentEntry);
        this->error = true;
    }
}


int Pass1::getLengthOf(string constant) {
    if (constant.c_str()[1] != '\''
        || constant.c_str()[constant.length() - 1] != '\'') {
        return -1;
    }
    if (toupper(constant.c_str()[0]) == 'X') {
        if (constant.length() >= 5 && (constant.length() % 2) != 0 && regex_match(constant.substr(2, constant.length() - 2), regex ("(\\d|[A-F])+"))) {
            return ((int) constant.length() - 3 )/ 2;
        } else {
            return -1;
        }

    } else if (toupper(constant.c_str()[0]) == 'C') {
        if (constant.length() >= 4) {
            return (int) constant.length() - 3;
        } else {
            return -1;
        }

    }
    return -1;
}

void Pass1::writeCurrenLineToIntermediateFile(int lineNumber, int locationCounter,
                                              int lenOfCurrentInstruction, Entry currentEntry) {
    if (lineNumber < 0) {
        numOfErrors++;
    }
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
        outfile << "\t\t\t\t\t\t***Duplicate lable definition***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -2) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***Wrong operand prefix***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -3) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***Invalid symbol name***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -4) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***Can not have forward reference here***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -5) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***Invalid expression***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -6) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***This instruction can not have lable***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -7) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***This instruction can not have operand***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -8) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***No END statement***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -9) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***Invalid literal***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -10) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***Operand format is not compatible with operation***" << endl;
        outfile.close();
        return;
    } else if (lineNumber == -11) {
        ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << "\t\t\t\t\t\t***End must be at the last line***" << endl;
        outfile.close();
        return;
    }
    string fixedLable = currentEntry.getLable();
    int length = (int) fixedLable.length();
    if (length < 8) {
        for (int i = 0; i < 8 - length; i++) {
            fixedLable.append(" ");
        }
    }
    string fixedOpcode = currentEntry.getOpCode();
    length = (int) fixedOpcode.length();
    if (length < 9) {
        for (int i = 0; i < 9 - length; i++) {
            fixedOpcode.append(" ");
        }
    }
    string fixedOperand = currentEntry.getOperand();
    length = (int) fixedOperand.length();
    if (length < 17) {
        for (int i = 0; i < 17 - length; i++) {
            fixedOperand.append(" ");
        }
    }
    fixedLable = to_upper(fixedLable);
    fixedOpcode = to_upper(fixedOpcode);
    if (currentEntry.getOpCode() != "BYTE" && currentEntry.getOperand().c_str()[0] != '=') {
        fixedOperand = to_upper(fixedOperand);
    }
    char stro[100];


    Utilities utilities;
    string address = utilities.decimalToHex(locationCounter - lenOfCurrentInstruction);

    sprintf(stro, "%-8d\t%6s\t\t%.8s\t\t%.8s\t\t%s\t%s",
            lineNumber,address.c_str(),
            fixedLable.c_str(),
            fixedOpcode.c_str(),
            fixedOperand.c_str(),
            currentEntry.getComment().c_str());
    ofstream outfile;
    outfile.open(outPath, ios_base::app);
    outfile << stro << endl;
    outfile.close();
    //delete stro;
}

void Pass1::printSymTable(SymTable symTable) {
    ofstream outfile;
    outfile.open(symTablePath, ios_base::app);
    cout << endl << "SymTable\tAddress" << endl << endl;
    outfile << endl << "SymTable\tAddress" << endl << endl;
    for(auto symbol : symTable.symbolTable) {
        string symbolName = symbol.first;
        int length = (int) symbolName.length();
        if (length < 8) {
            for (int i = 0; i < 8 - length; i++) {
                symbolName.append(" ");
            }
        }
        cout << symbolName << "\t" << hex << symbol.second << endl;
        outfile << symbolName << "\t" << hex << symbol.second << endl;
    }
    outfile.close();
}

void Pass1::printLitTable(LitTab litTable) {
    cout << endl << "LitTable\tLength\tAddress" << endl << endl;
    for(auto literal : litTable.litTable) {
        string litName = literal.first;
        int length = (int) litName.length();
        if (length < 8) {
            for (int i = 0; i < 8 - length; i++) {
                litName.append(" ");
            }
        }
        int address = literal.second.address;
        cout << litName << "\t" << literal.second.length << "\t" << hex << address << endl;
    }
}

string Pass1::to_upper(string str) {
    string upper_case_string = "";
    for (char c : str)
        upper_case_string += toupper(c);
    return upper_case_string;
}

int Pass1::valueOfExpression(string expression, SymTable symTable) {
    vector<string> terms{explode(expression, '+', '-', '*', '/')};
    char operations[terms.size()];
    if (expression.c_str()[0] == '-') {
        operations[0] = '-';
    } else {
        operations[0] = '+';
    }
    int counter = 1;
    for (int i = 1; i < expression.length(); i++) {
        if (expression.c_str()[i] == '-') {
            operations[counter++] = '-';
        } else if (expression.c_str()[i] == '+' || expression.c_str()[i] == '*' || expression.c_str()[i] == '/') {
            operations[counter++] = expression.c_str()[i];
        }
    }

    int value = 0;

    int i = 0;
    for(auto term:terms) {

        int numValue = 0;
        if (term.find(',') != std::string::npos) {
            return -1;
        } else if (is_number(term)) {
            istringstream buffer(term);

            buffer >> numValue;

        } else {
            if (!symTable.found(to_upper(term))) {
                return -2;
            }
            numValue = symTable.symbolTable[to_upper(term)];
        }
        switch(operations[i]) {
            case '-' :
                value -= numValue;
                break;
            case '+' :
                value += numValue;
                break;
            case '*' :
                value *= numValue;
                break;
            case '/' :
                value /= numValue;
                break;
            default :
                cout << "Invalid operation" << endl;
        }
        i++;
    }
    return value;

}

bool Pass1::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

const vector<string> Pass1::explode(const string& s, const char& c, const char& c1, const char& c2, const char& c3) {
    string buff{""};
    vector<string> v;
    for(auto n:s) {
        if(n != c && n!= c1 && n!= c2 && n!= c3) buff+=n; else
        if((n == c || n ==c1 || n!= c2 || n!= c3) && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);
    return v;
}

