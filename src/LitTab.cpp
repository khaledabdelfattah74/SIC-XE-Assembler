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

string LitTab::to_upper(string str) {
    string upper_case_string = "";
    for (char c : str)
        upper_case_string += toupper(c);
    return upper_case_string;
}

bool LitTab::insert(string name) {
    string temp = to_upper(name.substr(0, 2));
    temp.append(name.substr(2, name.length() - 2));
    name = temp;
    int length = lengthOfInstruction(name);
    if (length == -1) {
        return false;
    }
    if (this->litTable.count(name.substr(1, name.length() - 1)) == 0) {
        this->litTable.insert(
                make_pair(name.substr(1, name.length() - 1), *new Literal(name.substr(3, name.length() - 4),
                                                                          length, --initialAddress)));

        this->nonAssignedLiterals.insert(make_pair(initialAddress, name.substr(1, name.length() - 1)));
    }
    return true;
}

int LitTab::assignCurrentLiterals(int currentAddress, int linNo, string outPath) {
    while (nonAssignedLiterals.size() != 0) {
        string litNameToBeAssigned = nonAssignedLiterals[--lastAssignedLiteralID];
        litTable[litNameToBeAssigned].address = currentAddress;

        string directive;
        string value;
        string dump = "";
        if (toupper(litNameToBeAssigned.c_str()[0]) == 'W') {
            directive = "WORD";
            value = litNameToBeAssigned.substr(2, litNameToBeAssigned.length() - 3);
        } else {
            directive = "BYTE";
            value = litNameToBeAssigned;
        }
        string fixedLable = "="+litNameToBeAssigned;
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
        int intValue = 0;
        if (name.c_str()[3] == '-') {
            istringstream buffer(name.substr(4, 4));
            buffer >> intValue;
            if (name.length() <= 9 && name.length() >= 6 && intValue < 4096) {

                return 3;
            } else {
                return -1;
            }
        } else {
            istringstream buffer(name.substr(3, 4));
            buffer >> intValue;
            if (name.length() <= 8 && name.length() >= 5 && intValue < 4096) {

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
