//
//  ControlSection.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 6/11/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "ControlSection.hpp"

ControlSection::ControlSection(string sec_name, vector<IntermediateFileParser::entry> entries,
                               vector<string> ext_ref, vector<string> ext_def) {
    this->sec_name = sec_name;
    this->entries = entries;
    this->ext_ref = ext_ref;
    this->ext_def = ext_def;
}

string ControlSection::get_sec_name() {
    return this->sec_name;
}

vector<IntermediateFileParser::entry> ControlSection::get_enteries() {
    return this->entries;
}

vector<string> ControlSection::get_ext_ref() {
    return this->ext_ref;
}

vector<string> ControlSection::get_ext_def() {
    return this->ext_def;
}
