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
        {"+jGT", 4},
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
    this->operationCode = {
            {"ADD", "18"},
            {"+ADD", "18"},
            {"ADDR", "90"},
            {"CLEAR", "B4"},
            {"COMP", "28"},
            {"+COMP", "28"},
            {"COMPR", "A0"},
            {"DIV", "24"},
            {"+DIV", "24"},
            {"DIVR", "9C"},
            {"J", "3C"},
            {"+J", "3C"},
            {"JEQ", "30"},
            {"+JEQ", "30"},
            {"JGT", "34"},
            {"+jGT", "34"},
            {"JLT", "38"},
            {"+JLT", "38"},
            {"JSUB", "48"},
            {"+JSUB", "48"},
            {"LDA", "00"},
            {"+LDA", "00"},
            {"LDB", "68"},
            {"+LDB", "68"},
            {"LDCH", "50"},
            {"+LDCH", "50"},
            {"LDL", "08"},
            {"+LDL", "08"},
            {"LDS", "6C"},
            {"+LDS", "6C"},
            {"LDT", "74"},
            {"+LDT", "74"},
            {"LDX", "04"},
            {"+LDX", "04"},
            {"MUL", "20"},
            {"+MUL", "20"},
            {"MULR", "98"},
            {"RD", "D8"},
            {"+RD", "D8"},
            {"RMO", "AC"},
            {"RSUB", "4C"},
            {"+RSUB", "4C"},
            {"SHIFTL", "A4"},
            {"SHIFTR", "A8"},
            {"STA", "0C"},
            {"+STA", "0C"},
            {"STB", "78"},
            {"+STB", "78"},
            {"STCH", "54"},
            {"+STCH", "54"},
            {"STL", "14"},
            {"+STL", "14"},
            {"STS", "7C"},
            {"+STS", "7C"},
            {"STT", "84"},
            {"+STT", "84"},
            {"STX", "10"},
            {"+STX", "10"},
            {"SUB", "1C"},
            {"+SUB", "1C"},
            {"SUBR", "94"},
            {"TD", "E0"},
            {"+TD", "E0"},
            {"TIX", "2C"},
            {"+TIX", "2C"},
            {"TIXR", "B8"},
            {"WD", "DC"},
            {"+WD", "DC"}
        };

}

OpTable::~OpTable() {
}

int OpTable::lengthOf(std::string opCode) {
    int size = this->operationTable[opCode];
    return size;
}
string OpTable::getOperationCode(string operation)
{
	return this->operationCode[operation];
}

bool OpTable::found(std::string lable) {
    if (this->operationTable.count(lable) == 0) {
        return false;
    } else {
        return true;
    }
}
