//
// Created by ayman on 06/06/18.
//

#include "ObjectProgramGenerator.h"
#include "OpTable.hpp"
#include "Utilities.h"

string generateModificationRecords();

void ObjectProgramGenerator::generate_program_code(vector<IntermediateFileParser::entry> entries) {
    string output;
    output.append(generate_header_record(entries));
    output.append(generate_text_records(entries));
    output.append(generate_modification_records(entries));
    output.append(generate_end_record(entries));
    write_string_to_file(output,"/home/sajed/CLionProjects/untitled/ObjectCode.txt");
}

string ObjectProgramGenerator::generate_text_records(vector<IntermediateFileParser::entry> entries) const {
    vector<string> objectCodes = entries_to_object_codes(entries);
    Utilities utilities;
    string text_records;
    int current_address = utilities.hexToDecimal(entries[0].address);
    int text_length = 0;
    text_records.append("T");
    text_records.append(entries[0].address);
    int text_length_ind = text_records.length();
    text_records.append("XX");
    for (int i = 1; i < entries.size()-1; ++i) {
        if(current_address != utilities.hexToDecimal(entries[i].address)) {
            current_address = utilities.hexToDecimal(entries[i].address);
            text_records.append("\n");
            string text_length_hex = utilities.decimalToHex(text_length);
            text_records[text_length_ind] = text_length_hex[4];
            text_records[text_length_ind+1] = text_length_hex[5];
            text_records.append("T");
            text_records.append(entries[i].address);
            text_length_ind = text_records.length();
            text_records.append("XX");
            text_records.append(objectCodes[i-1]);
            text_length = objectCodes[i-1].length()/2;
        } else {
            if(text_length + objectCodes[i-1].length()/2 <= 30) {
                current_address += objectCodes[i-1].length()/2;
                text_records.append(objectCodes[i-1]);
                text_length += objectCodes[i-1].length()/2;
            } else {
                current_address += objectCodes[i-1].length()/2;
                text_records.append("\n");
                string text_length_hex = utilities.decimalToHex(text_length);
                text_records[text_length_ind] = text_length_hex[4];
                text_records[text_length_ind+1] = text_length_hex[5];
                text_records.append("T");
                text_records.append(entries[i].address);
                text_length_ind = text_records.length();
                text_records.append("XX");
                text_records.append(objectCodes[i-1]);
                text_length = objectCodes[i-1].length()/2;
            }
        }
    }
    text_records.append("\n");
    string text_length_hex = utilities.decimalToHex(text_length);
    text_records[text_length_ind] = text_length_hex[4];
    text_records[text_length_ind+1] = text_length_hex[5];
    return text_records;
}

string ObjectProgramGenerator::generate_modification_records(vector<IntermediateFileParser::entry> entries) {
    Utilities utilities;
    if(entries[0].address == "000000") {
        string modifications;
        for (int i = 0; i < entries.size(); ++i) {
            if(entries[i].e) {
                modifications.append("M");
                int decimal_modification_address = utilities.hexToDecimal(entries[i].address) + 1;
                string hex_modification_address = utilities.decimalToHex(decimal_modification_address);
                modifications.append(hex_modification_address);
                modifications.append("05\n");
            }
        }
        return modifications;
    }
    return "";
}


vector<string> ObjectProgramGenerator::entries_to_object_codes(vector<IntermediateFileParser::entry> entries)const {
    vector<string> object_codes;
    for(int i = 1;i < entries.size()-1;i++) {
        object_codes.push_back(entry_to_object_code(entries[i]));
    }
    return object_codes;
}

string ObjectProgramGenerator::entry_to_object_code(IntermediateFileParser::entry entry)const {
    string op_code = entry.operationCode;
    string object_code;
    OpTable operation_table;
    Utilities utilities;
    if(op_code == "WORD") {
        object_code = utilities.hexWord(entry.operand[0]);
    } else if(op_code == "BYTE") {
        object_code = utilities.hexByte(entry.operand[0]);
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
    return object_code;
}

string ObjectProgramGenerator::forth_format_to_hex(IntermediateFileParser::entry entry)const {
    vector<bool> entry_start_binary = entry_start_to_binary(entry);
    string operand = entry.displacemnet;
    if(operand.length() > 5)
        operand = operand.substr(operand.length()-5,5);
    while (operand.length() < 5) {
        operand.insert(0,"0");
    }
    //vector<bool> operand_binary = hex_string_to_binary(operand);
    string object_hex = binary_to_hex_string(entry_start_binary).substr(3,3);
    object_hex.append(operand);
    return  object_hex;
}

string ObjectProgramGenerator::third_format_to_hex(IntermediateFileParser::entry entry)const {
    vector<bool> entry_start_binary = entry_start_to_binary(entry);
    string operand = entry.displacemnet;
    if(operand.length() > 3)
        operand = operand.substr(operand.length()-3,3);
    while (operand.length() < 3) {
            operand.insert(0,"0");
    }
    //vector<bool> operand_binary = hex_string_to_binary(operand);

    string object_hex = binary_to_hex_string(entry_start_binary).substr(3,3);
    object_hex.append(operand);
    return  object_hex;
}

vector<bool> ObjectProgramGenerator::entry_start_to_binary(const IntermediateFileParser::entry entry)const {
    OpTable operation_table;
    string op_code = entry.operationCode;
    vector<bool> binary = hex_string_to_binary(operation_table.getOperationCode(op_code));
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
    return binary;
}

string ObjectProgramGenerator::binary_to_hex_string(vector<bool> binary)const {
    string hex;
    int decimal = 0;
    int base = 1;
    for (int i = 0; i < binary.size(); ++i) {
        if(binary[binary.size()-i-1])
            decimal += base;
        base *= 2;
    }
    Utilities utilities;
    return utilities.decimalToHex(decimal);
}

string ObjectProgramGenerator::register_to_hex(string reg)const {
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
    return "";
}

vector<bool> ObjectProgramGenerator::hex_string_to_binary(string hex)const {
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

string ObjectProgramGenerator::generate_header_record(vector<IntermediateFileParser::entry> entries) {
    string header;
    Utilities utilities;
    header.append("H");
    string porgram_name = entries[0].label;
    while (porgram_name.length() < 6)
        porgram_name.push_back(' ');
    header.append(porgram_name);
    header.append(entries[0].address);
    header.append(utilities.decimalToHex(utilities.hexToDecimal(entries[entries.size()-1].address) - utilities.hexToDecimal(entries[0].address)));
    header.append("\n");
    return header;
}

string ObjectProgramGenerator::generate_end_record(vector<IntermediateFileParser::entry> entries) {
    string end_record;
    end_record.append("E");
    end_record.append(entries[0].address);
    return end_record;
}

void ObjectProgramGenerator::write_string_to_file(string str, string file_path) {
    ofstream out (file_path);
    out << str;
}

