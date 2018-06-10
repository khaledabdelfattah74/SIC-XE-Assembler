//
//  Validator.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/29/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef Validator_hpp
#define Validator_hpp

#include <stdio.h>
#include <string>

#include "OpTable.hpp"

using namespace std;

class Validator {
public:
    Validator();
    bool check_vaidity(string operation, string operand);
private:
    OpTable opTable;
};

#endif /* Validator_hpp */
