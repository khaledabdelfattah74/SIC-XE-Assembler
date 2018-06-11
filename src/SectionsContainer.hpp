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
#include "ControlSection.hpp"
using namespace std;

class SectionsContainer {
public:
    static SectionsContainer get_instance();
    void insert(string sec_name, ControlSection);
    ControlSection get_section(string sec_name);
private:
    SectionsContainer();
    SectionsContainer *container = nullptr;
    unordered_map<string, ControlSection> sections;
};
#endif /* SectionsContainer_hpp */
