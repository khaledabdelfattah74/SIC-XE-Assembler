#include "LitTab.h"
#include <string>
#include <cstring>
#include <ctype.h>
#include "SymTable.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

LitTab::LitTab()
{
    //ctor
}

LitTab::~LitTab()
{
    //dtor
}

bool LitTab::insert(string name) {
    int length = lengthOfInstruction(name);
    if (length == -1) {
        return false;
    }
    this->litTable.insert(make_pair(name.substr(1, name.length() - 1), *new Literal(name.substr(3, name.length() - 4),
                                                        length, --initialAddress)));
    this->nonAssignedLiterals.insert(make_pair(initialAddress, name.substr(1, name.length() - 1)));
    return true;
}

int LitTab::assignCurrentLiterals(int currentAddress, int linNo, string outPath) {
    while (nonAssignedLiterals.size() != 0) {
        string litNameToBeAssigned = nonAssignedLiterals[--lastAssignedLiteralID];
        litTable[litNameToBeAssigned].address = currentAddress;

        string directive;
        string value;
        string dump = "";
        if (litNameToBeAssigned.c_str()[0] == 'w' || litNameToBeAssigned.c_str()[0] == 'W') {
            directive = "WORD";
            value = litNameToBeAssigned.substr(2, litNameToBeAssigned.length() - 3);
        } else {
            directive = "BYTE";
            value = litNameToBeAssigned;
        }
        string fixedLable = litNameToBeAssigned;
        int length = (int) fixedLable.length();
        if (length < 8) {
            for (int i = 0; i < 8 - length; i++) {
                fixedLable.append(" ");
            }
        }
        string fixedOpcode = directive;
        length = (int) fixedOpcode.length();
        if (length < 9) {
            for (int i = 0; i < 9 - length; i++) {
                fixedOpcode.append(" ");
            }
        }
        string fixedOperand = value;
        length = (int) fixedOperand.length();
        if (length < 17) {
            for (int i = 0; i < 17 - length; i++) {
                fixedOperand.append(" ");
            }
        }
        char stro[100];
        sprintf(stro, "%-8d\t%06x\t\t%.15s\t\t%.8s\t\t%.18s\t%s",
                linNo,currentAddress,
                fixedLable.c_str(),
                fixedOpcode.c_str(),
                fixedOperand.c_str(),
                dump.c_str());
        std::ofstream outfile;
        outfile.open(outPath, ios_base::app);
        outfile << stro << endl;
        outfile.close();

        currentAddress += litTable[litNameToBeAssigned].length;
        nonAssignedLiterals.erase(lastAssignedLiteralID);
    }
    return currentAddress;
}


int LitTab::lengthOfInstruction(string name) {
    if (toupper(name.c_str()[1]) == 'W') {
        if (name.c_str()[3] == '-') {
            if (name.length() <= 9 && name.length() >= 6) {
                return 3;
            } else {
                return -1;
            }
        } else {
            if (name.length() <= 8 && name.length() >= 5) {
                return 3;
            } else {
                return -1;
            }
        }
        return 3;
    } else if (toupper(name.c_str()[1]) == 'X') {
        if (name.length() >= 6 && (name.length() % 2) == 0) {
                return ((int) name.length() - 4 )/ 2;
            } else {
                return -1;
            }

    } else if (toupper(name.c_str()[1]) == 'C') {
        if (name.length() >= 5) {
                return (int) name.length() - 4;
            } else {
                return -1;
            }

    } else {
        return -1;
    }
}

int LitTab::size() {
    return (int) this->litTable.size();
}

bool LitTab::found(string lable) {
    if (this->litTable.count(lable) == 0) {
        return false;
    } else {
        return true;
    }
}
