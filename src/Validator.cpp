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
const regex literal ("(\\=)(C|W|X)\\'(\\w)+\\'");
const regex literal2 ("(\\=)(C|W|X)\\'(\\-)(\\w)+\\'");

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
        else if (regex_match(operand, literal) || regex_match(operand, literal2)) {
            string value = "";
            for (int i = 3; i < operand.length() - 1; i ++)
                value += operand[i];
            if (operand[1] == 'W')
                return regex_match(value, regex ("(\\-)\\d+")) || regex_match(value, regex ("\\d+"));
            else if (operand[1] == 'X')
                return regex_match(value, regex ("(\\d|[A-F])+"));
            else if (operand[1] == 'C')
                return regex_match(value, regex ("\\w+"));
        } else
            return false;
    }
    return false;
}
