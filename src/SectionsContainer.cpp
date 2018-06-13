//
//  SectionsContainer.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 6/11/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "SectionsContainer.hpp"

SectionsContainer SectionsContainer::get_instance() {
    if (!container)
        container = new SectionsContainer();
    return *container;
}

void SectionsContainer::insert(string sec_name, ControlSection section) {
    this->sections[sec_name] = section;
}

ControlSection SectionsContainer::get_section(string sec_name) {
    return this->sections[sec_name];
}

