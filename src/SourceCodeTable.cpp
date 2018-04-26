//
//  SourceCodeTable.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "SourceCodeTable.hpp"

SourceCodeTable::SourceCodeTable() {
    
}

void SourceCodeTable::addEntry(Entry entry) {
    this->entries.push(entry);
}

Entry* SourceCodeTable::fetchNextEntry() {
    Entry* firstIsertedEntry = &this->entries.front();
    entries.pop();
    return firstIsertedEntry;
}

SourceCodeTable::~SourceCodeTable() {
    // TODO Auto-generated destructor stub
}
