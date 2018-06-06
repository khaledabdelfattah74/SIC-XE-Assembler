//
// Created by ayman on 06/06/18.
//

#include "ObjectProgramGenerator.h"
#include "OpTable.hpp"

vector<string> entries_to_object_codes(vector<IntermediateFileParser::entry> entries);

string entry_to_object_code(IntermediateFileParser::entry entry);

string register_to_hex(string reg);

vector<bool> hex_string_to_binary(string hex);

string binary_to_hex_string(vector<bool> binary);

string third_format_to_hex(IntermediateFileParser::entry &entry);

string forth_format_to_hex(IntermediateFileParser::entry entry);

void generate_program_code(vector<IntermediateFileParser::entry> entries) {
    vector<string> objectCodes = entries_to_object_codes(entries);
    string output = "H";
    string porgram_name = entries[0].label;
    while (porgram_name.length() < 6)
        porgram_name.push_back(' ');
    output.append(porgram_name);
    output.append(entries[0].address);

}

vector<string> entries_to_object_codes(vector<IntermediateFileParser::entry> entries) {
    vector<string> object_codes;
    for(int i = 1;i < entries.size()-1;i++) {
        object_codes.push_back(entry_to_object_code(entries[i]));
    }
    return object_codes;
}

string entry_to_object_code(IntermediateFileParser::entry entry) {
    string op_code = entry.operationCode;
    string object_code;
    OpTable operation_table;
    if(op_code == "WORD") {
        // Todo
    } else if(op_code == "BYTE") {
        // Todo
    } else if(operation_table.lengthOf(op_code) == 1){
        object_code = operation_table.getOperationCode(op_code);
    } else if(operation_table.lengthOf(op_code) == 2){
        object_code = operation_table.getOperationCode(op_code);
        object_code.append(register_to_hex(entry.operand[0]));
        object_code.append(register_to_hex(entry.operand[1]));
    } else if(operation_table.lengthOf(op_code) == 3) {
        object_code = third_format_to_hex(entry);
    } else if(operation_table.lengthOf(op_code) == 4) {
        object_code = forth_format_to_hex(entry);
    }
}

string forth_format_to_hex(IntermediateFileParser::entry entry) {
    vector<bool> binary;
    string op_code = entry.operationCode;
    OpTable operation_table;
    binary= hex_string_to_binary(operation_table.getOperationCode(op_code));
    if(entry.n)
        binary[6] = true;
    if(entry.i)
        binary[7] = true;
    if(entry.x)
        binary.push_back(true);
    else
        binary.push_back(false);
    if(entry.b)
        binary.push_back(true);
    else
        binary.push_back(false);
    if(entry.p)
        binary.push_back(true);
    else
        binary.push_back(false);
    if(entry.e)
        binary.push_back(true);
    else
        binary.push_back(false);
    string operand = entry.displacemnet;
    while (operand.length() < 5) {
        operand.reserve();
        operand.push_back('0');
        operand.reserve();
    }
    return binary_to_hex_string(binary) + operand;
}

string third_format_to_hex(IntermediateFileParser::entry &entry) {
    vector<bool> binary;
    string op_code = entry.operationCode;
    OpTable operation_table;
    binary= hex_string_to_binary(operation_table.getOperationCode(op_code));
    if(entry.n)
            binary[6] = true;
    if(entry.i)
            binary[7] = true;
    if(entry.x)
            binary.push_back(true);
        else
            binary.push_back(false);
    if(entry.b)
            binary.push_back(true);
        else
            binary.push_back(false);
    if(entry.p)
            binary.push_back(true);
        else
            binary.push_back(false);
    if(entry.e)
            binary.push_back(true);
        else
            binary.push_back(false);
    string operand = entry.displacemnet;
    while (operand.length() < 3) {
            operand.reserve();
            operand.push_back('0');
            operand.reserve();
    }
    return binary_to_hex_string(binary) + operand;
}

string binary_to_hex_string(vector<bool> binary) {
    string hex;
    for (int i = binary.size(); i >= 0; i=i-4) {
        int base = 1;
        int dec = 0;
        for (int j = i; j >= 0 && j > i-4; --j) {
            if(binary[j])
                dec += base;
            base *= 2;
        }
        if(dec < 10)
            hex.push_back(dec+'0');
        else
            hex.push_back(dec-10+'A');
    }
    return hex;
}

string register_to_hex(string reg) {
    switch (reg[0]) {
        case 'A':
            return "0";
        case 'X':
            return "1";
        case 'L':
            return "2";
        case 'B':
            return "3";
        case 'S':
            return "4";
        case 'T':
            return "5";
        case 'F':
            return "6";
    }
}

vector<bool> hex_string_to_binary(string hex) {
    vector<bool> res;
    for(int i = 0;i < hex.length();i++) {
        switch (hex[i]) {
            case '0' :
                res.push_back(false);
                res.push_back(false);
                res.push_back(false);
                res.push_back(false);
                break;
            case '1' :
                res.push_back(false);
                res.push_back(false);
                res.push_back(false);
                res.push_back(true);
                break;
            case '2' :
                res.push_back(false);
                res.push_back(false);
                res.push_back(true);
                res.push_back(false);
                break;
            case '3' :
                res.push_back(false);
                res.push_back(false);
                res.push_back(true);
                res.push_back(true);
                break;
            case '4' :
                res.push_back(false);
                res.push_back(true);
                res.push_back(false);
                res.push_back(false);
                break;
            case '5' :
                res.push_back(false);
                res.push_back(true);
                res.push_back(false);
                res.push_back(true);
                break;
            case '6' :
                res.push_back(false);
                res.push_back(true);
                res.push_back(true);
                res.push_back(false);
                break;
            case '7' :
                res.push_back(false);
                res.push_back(true);
                res.push_back(true);
                res.push_back(true);
                break;
            case '8' :
                res.push_back(true);
                res.push_back(false);
                res.push_back(false);
                res.push_back(false);
                break;
            case '9' :
                res.push_back(true);
                res.push_back(false);
                res.push_back(false);
                res.push_back(true);
                break;
            case 'A' :
                res.push_back(true);
                res.push_back(false);
                res.push_back(true);
                res.push_back(false);
                break;
            case 'B' :
                res.push_back(true);
                res.push_back(false);
                res.push_back(true);
                res.push_back(true);
                break;
            case 'C' :
                res.push_back(true);
                res.push_back(true);
                res.push_back(false);
                res.push_back(false);
                break;
            case 'D' :
                res.push_back(true);
                res.push_back(true);
                res.push_back(false);
                res.push_back(true);
                break;
            case 'E' :
                res.push_back(true);
                res.push_back(true);
                res.push_back(true);
                res.push_back(false);
                break;
            case 'F' :
                res.push_back(true);
                res.push_back(true);
                res.push_back(true);
                res.push_back(true);
                break;
        }
    }
    return res;
}

