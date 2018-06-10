//
//  SymTable.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "SymTable.hpp"
#include <string>
#include <iostream>

using namespace std;
SymTable::SymTable() {

}

SymTable::~SymTable() {
}

void SymTable::insert(string lable, int address, string sectionName) {
    this->symbolTable.insert(make_pair(lable, make_pair(address, sectionName)));
}

int SymTable::size() {
    return (int) this->symbolTable.size();
}

bool SymTable::found(string lable) {
    if (this->symbolTable.count(lable) == 0) {
        return false;
    } else {
        return true;
    }
}
