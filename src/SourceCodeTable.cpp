//
//  SourceCodeTable.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "SourceCodeTable.hpp"
#include <iostream>

SourceCodeTable::SourceCodeTable() {

}

void SourceCodeTable::addEntry(Entry entry) {
    this->entries.push(entry);
}

Entry* SourceCodeTable::fetchNextEntry() {
    Entry* firstIsertedEntry = &this->entries.front();
    this->entries.pop();
    return firstIsertedEntry;
}

int SourceCodeTable::size() {
    return (int) this->entries.size();
}

SourceCodeTable::~SourceCodeTable() {
}

