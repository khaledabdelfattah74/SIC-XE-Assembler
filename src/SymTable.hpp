//
//  SymTable.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef SymTable_hpp
#define SymTable_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>

using namespace std;

class SymTable {
public:
    SymTable();
    virtual ~SymTable();
    void insert(string, int);
    bool found(string);
private:
    unordered_map<string, int> symbolTable;
};

#endif /* SymTable_hpp */
