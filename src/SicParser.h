/*
 * SicParser.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef SICPARSER_H_
#define SICPARSER_H_
#include "SourceCodeTable.h"
#include <string>

using namespace std;
class SicParser {
public:
    SicParser();
    virtual ~SicParser();
    SourceCodeTable parse(string path);
    ;
};

#endif /* SICPARSER_H_ */
