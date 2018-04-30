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
    this->litTable.insert(make_pair(name.substr(1, name.length() - 1), *new Literal(name.substr(3, name.length() - 3),
                                                        length, --initialAddress)));
    this->nonAssignedLiterals.insert(make_pair(initialAddress, name.substr(1, name.length() - 1)));
    return true;
}

int LitTab::assignCurrentLiterals(int currentAddress, int linNo, string outPath) {
    while (nonAssignedLiterals.size() != 0) {
        string litNameToBeAssigned = nonAssignedLiterals[--lastAssignedLiteralID];
        litTable[litNameToBeAssigned].address = currentAddress;

        char stro[100];
        string dump = "";
        sprintf(stro, "%-8d\t%06x\t\t%.8s\t\t%.8s\t\t%.18s\t%s",
                linNo,currentAddress,
                "*       ",
                litNameToBeAssigned.c_str(),
                dump.c_str(),
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
        return 3;
    } else if (toupper(name.c_str()[1]) == 'X') {
        return ((int) name.length() - 4 )/ 2;
    } else if (toupper(name.c_str()[1]) == 'C') {
        return (int) name.length() - 4;
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
