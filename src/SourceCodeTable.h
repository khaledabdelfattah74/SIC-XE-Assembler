/*
 * SourceCodeTable.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef SOURCECODETABLE_H_
#define SOURCECODETABLE_H_
#include <queue>
#include "Entry.h"

using namespace std;

class SourceCodeTable {
public:
	SourceCodeTable();
	virtual ~SourceCodeTable();
	void addEntry(Entry entry);
	Entry fetchNextEntry();

private:
	queue<Entry> entries;
};

#endif /* SOURCECODETABLE_H_ */
