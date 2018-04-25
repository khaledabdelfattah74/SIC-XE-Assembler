/*
 * SicParser.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef SICPARSER_H_
#define SICPARSER_H_
#include "SourceCodeTable.h"
class SicParser {
public:
	SicParser(FILE * sourceCode);
	virtual ~SicParser();
	SourceCodeTable parse();
private:
	FILE * sourceCode;
};

#endif /* SICPARSER_H_ */
