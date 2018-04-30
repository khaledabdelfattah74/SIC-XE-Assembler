//
//  Validator.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/29/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "Validator.hpp"
#include <regex>

const regex twoRegisters ("(A|B|X|L|T|F|S|P),(A|B|X|L|T|F|S|P)");
const regex oneRegister ("(A|B|X|L|T|F|S|P)");
const regex indexing ("(\\w)+,X");
const regex memoryAddressing ("(#|@)*([A-Z])(\\w)*");
const regex immediateAddressing ("(#|@)*(\\d)+");
const regex notRegester ("(#|@)*(A|B|X|L|T|F|S|P)");
const regex expression ("(\\w)+(\\-|\\+)(\\w)+");
const regex notValid ("([A-Z](\\w)*(\\+)[A-Z](\\w)*)|((\\d)+(\\-)[A-Z](\\w)*)");


Validator::Validator() {
    this->opTable = * new OpTable();
}

bool Validator::check_vaidity(string operation, string operand) {
    int lengthOfInstruction = this->opTable.lengthOf(operation);
    if (lengthOfInstruction == 2) {
        if (operation == "CLEAR" || operation == "TIXR")
            return regex_match(operand, oneRegister);
        return regex_match(operand, twoRegisters);
    } else if (operation == "RSUB") {
        return operand.length() == 0;
    } else if (regex_match(operand, expression)) {
        return !regex_match(operand, notValid);
    } else {
        if (regex_match(operand, oneRegister))
            return false;
        if (regex_match(operand, indexing) && !regex_match(operand, twoRegisters))
            return true;
        else if ((regex_match(operand, memoryAddressing) || regex_match(operand, immediateAddressing))
                 && !regex_match(operand, notRegester))
            return true;
        else
            return false;
    }
    return false;
}
