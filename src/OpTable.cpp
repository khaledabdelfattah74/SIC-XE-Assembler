//
//  OpTable.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "OpTable.hpp"

OpTable::OpTable() {
    this->operationTable = {
        {"ADD", 3},
        {"+ADD", 4},
        {"ADDR", 2},
        {"CLEAR", 2},
        {"COMP", 3},
        {"+COMP", 4},
        {"COMPR", 2},
        {"DIV", 3},
        {"+DIV", 4},
        {"DIVR", 2},
        {"J", 3},
        {"+J", 4},
        {"JEQ", 3},
        {"+JEQ", 4},
        {"JGT", 3},
        {"+JGT", 4},
        {"JLT", 3},
        {"+JLT", 4},
        {"JSUB", 3},
        {"+JSUB", 4},
        {"LDA", 3},
        {"+LDA", 4},
        {"LDB", 3},
        {"+LDB", 4},
        {"LDCH", 3},
        {"+LDCH", 4},
        {"LDL", 3},
        {"+LDL", 4},
        {"LDS", 3},
        {"+LDS", 4},
        {"LDT", 3},
        {"+LDT", 4},
        {"LDX", 3},
        {"+LDX", 4},
        {"MUL", 3},
        {"+MUL", 4},
        {"MULR", 2},
        {"RD", 3},
        {"+RD", 4},
        {"RMO", 2},
        {"RSUB", 3},
        {"+RSUB", 4},
        {"SHIFTL", 2},
        {"SHIFTR", 2},
        {"STA", 3},
        {"+STA", 4},
        {"STB", 3},
        {"+STB", 4},
        {"STCH", 3},
        {"+STCH", 4},
        {"STL", 3},
        {"+STL", 4},
        {"STS", 3},
        {"+STS", 4},
        {"STT", 3},
        {"+STT", 4},
        {"STX", 3},
        {"+STX", 4},
        {"SUB", 3},
        {"+SUB", 4},
        {"SUBR", 3},
        {"TD", 3},
        {"+TD", 4},
        {"TIX", 3},
        {"+TIX", 4},
        {"TIXR", 2},
        {"WD", 3},
        {"+WD", 4}
    };

}

OpTable::~OpTable() {
}

int OpTable::lengthOf(std::string opCode) {
    int size = this->operationTable[opCode];
    return size;
}

bool OpTable::found(std::string lable) {
    if (this->operationTable.count(lable) == 0) {
        return false;
    } else {
        return true;
    }
}
