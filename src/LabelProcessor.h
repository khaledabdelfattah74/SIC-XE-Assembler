#ifndef SRC_LABELPROCESSOR_H_
#define SRC_LABELPROCESSOR_H_

#include "IntermediateFileParser.hpp"
#include <unordered_map>

class LabelProcessor {
public:
	LabelProcessor();
	virtual ~LabelProcessor();
	unordered_map<string,string> assignLabelAddresses(vector<IntermediateFileParser::entry> *vectorToFilter);
	bool getErrorFlag();
private:
	bool errorFlag = false;
	bool canBeRemved(IntermediateFileParser::entry entryToCheck);
};

#endif
