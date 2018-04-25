/*
 * SourceCodeTable.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#include "SourceCodeTable.h"

SourceCodeTable::SourceCodeTable() {

}

void SourceCodeTable::addEntry(Entry entry) {
	this->entries.push(entry);
}

Entry SourceCodeTable::fetchNextEntry() {
	Entry firstIsertedEntry = this->entries.front();
	entries.pop();
	return firstIsertedEntry;
}

SourceCodeTable::~SourceCodeTable() {
	// TODO Auto-generated destructor stub
}

