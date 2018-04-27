//
//  SymTable.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "SymTable.hpp"
#include <string>

using namespace std;
SymTable::SymTable() {

}

SymTable::~SymTable() {
}

void SymTable::insert(string lable, int address) {
    this->symbolTable.insert(make_pair(lable, address));
}
bool SymTable::found(string lable) {
    if (this->symbolTable.count(lable) == 0) {
        return false;
    } else {
        return true;
    }
}
