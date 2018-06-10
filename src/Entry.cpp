//
//  Entry.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "Entry.hpp"

Entry::Entry(string lable, string opCode, string operand, string comment, bool commentLine) {
    this->lable = lable;
    this->opCode = opCode;
    this->operand = operand;
    this->comment = comment;
    this->commentLine = commentLine;
}

string Entry::getLable() {
    return this->lable;
}

string Entry::getOpCode() {
    return this->opCode;
}

string Entry::getOperand() {
    return this->operand;
}

string Entry::getComment() {
    return this->comment;
}

bool Entry::isCommentLine() {
    return this->commentLine;
}
