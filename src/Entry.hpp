//
//  Entry.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef Entry_hpp
#define Entry_hpp

#include <stdio.h>
#include<string>

using namespace std;

class Entry {
public:
    Entry(string lable, string opCode, string operand, string comment, string isCommentLine);
    string getLable();
    string getOpCode();
    string getOperand();
    string getComment();
    string isCommentLine();
private:
    string lable;
    string opCode;
    string operand;
    string comment;
    string commentLine;
};

#endif /* Entry_hpp */
