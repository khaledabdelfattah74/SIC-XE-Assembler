//
//  OpTable.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef OpTable_hpp
#define OpTable_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>

using namespace std;

class OpTable {
public:
    OpTable();
    virtual ~OpTable();
    bool found(std::string);
    int lengthOf(std::string);
private:
    unordered_map<string, int> operationTable;
};

#endif /* OpTable_hpp */
