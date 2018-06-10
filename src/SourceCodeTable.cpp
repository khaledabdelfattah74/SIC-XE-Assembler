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

Entry SourceCodeTable::fetchNextEntry() {
    Entry firstInsertedEntry = * new Entry(
            entries.front().getLable(),
            entries.front().getOpCode(),
            entries.front().getOperand(),
            entries.front().getComment(),
            entries.front().isCommentLine());
    this->entries.pop();
    return firstInsertedEntry;
}

int SourceCodeTable::size() {
    return (int) this->entries.size();
}

SourceCodeTable::~SourceCodeTable() {
}

