//
//  SourceCodeTable.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef SourceCodeTable_hpp
#define SourceCodeTable_hpp

#include <stdio.h>
#include <queue>
#include "Entry.hpp"

using namespace std;

class SourceCodeTable {
public:
    SourceCodeTable();
    virtual ~SourceCodeTable();
    void addEntry(Entry entry);
    Entry* fetchNextEntry();
    int size();

private:
    queue<Entry> entries;
};

#endif /* SourceCodeTable_hpp */
