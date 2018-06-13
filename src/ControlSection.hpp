//
//  ControlSection.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 6/11/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef ControlSection_hpp
#define ControlSection_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "IntermediateFileParser.hpp"

using namespace std;
class ControlSection {
public:
    ControlSection();
    string get_sec_name();
    vector<IntermediateFileParser::entry> get_enteries();
    vector<string> get_ext_ref();
    vector<string> get_ext_def();
    string sec_name;
    vector<IntermediateFileParser::entry> entries;
    vector<string> ext_ref;
    vector<string> ext_def;
private:
    
};
#endif /* ControlSection_hpp */
