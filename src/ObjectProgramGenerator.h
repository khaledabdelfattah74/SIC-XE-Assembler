//
// Created by ayman on 06/06/18.
//

#ifndef SIC_XE_ASSEMBLER_OBJECTCODEGENERATOR_H
#define SIC_XE_ASSEMBLER_OBJECTCODEGENERATOR_H

#include "ControlSection.hpp"
#include "IntermediateFileParser.hpp"
#include <unordered_map>
class ObjectProgramGenerator {
public:
    ObjectProgramGenerator(unordered_map<string,string> labelAddresses,
                           unordered_map<string, ControlSection>);
    
    string generate_program_code(vector<IntermediateFileParser::entry>);

    string generate_modification_records(vector<IntermediateFileParser::entry> entries);

    vector<string> entries_to_object_codes(vector<IntermediateFileParser::entry> entries)const;

    string entry_to_object_code(IntermediateFileParser::entry entry)const;

    string forth_format_to_hex(IntermediateFileParser::entry entry)const;

    string third_format_to_hex(IntermediateFileParser::entry entry)const;

    string binary_to_hex_string(vector<bool> binary)const;

    string register_to_hex(string reg)const;

    vector<bool> hex_string_to_binary(string hex)const;

    string generate_header_record(vector<IntermediateFileParser::entry> entries);

    vector<bool> entry_start_to_binary(const IntermediateFileParser::entry entry)const;

    string generate_text_records(vector<IntermediateFileParser::entry> entries) const;

    string generate_end_record(vector<IntermediateFileParser::entry> entries);
    
    string generate_definition_record(vector<IntermediateFileParser::entry> entries);
    
    string generate_referenc_recod(vector<IntermediateFileParser::entry> entries);

    void write_string_to_file(string str, string file_path);
private:
    unordered_map<string, ControlSection> container;
    string porgram_name;
    unordered_map<string,string> labelAddresses;
};


#endif //SIC_XE_ASSEMBLER_OBJECTCODEGENERATOR_H
