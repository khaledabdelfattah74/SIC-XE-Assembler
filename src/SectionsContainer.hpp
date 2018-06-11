//
//  SectionsContainer.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 6/11/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef SectionsContainer_hpp
#define SectionsContainer_hpp

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include "IntermediateFileParser.hpp"
using namespace std;

class SectionsContainer {
public:
    
    void insert(string sec_name, vector<IntermediateFileParser::entry>,
                vector<string> ext_ref, vector<string> ext_def);
};
#endif /* SectionsContainer_hpp */
