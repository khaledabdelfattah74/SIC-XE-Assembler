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
    string getOperationCode(string operation);
private:
    unordered_map<string, int> operationTable;
    unordered_map<string, string> operationCode;
};

#endif /* OpTable_hpp */
