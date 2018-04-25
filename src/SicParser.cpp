/*
 * SicParser.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#include "SicParser.h"
#include "SourceCodeTable.h"

SicParser::SicParser(FILE * sourceCode) {
	this->sourceCode = sourceCode;
}

SicParser::~SicParser() {
	// TODO Auto-generated destructor stub
}

SourceCodeTable parse() {
	SourceCodeTable sourceCodeTable;
	//TODO IMPORTATNT if a field in an entry is not exist insert it as a string with length zero
	//TODO parsing code goes here to fill and return a source code table object with entries.
	return sourceCodeTable;
}
