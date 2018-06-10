#ifndef SRC_ADDRESINGMODIFIER_H_
#define SRC_ADDRESINGMODIFIER_H_

#include "IntermediateFileParser.hpp"

class AddresingModifier {
public:
	AddresingModifier();
	virtual ~AddresingModifier();
	void setVectorAddressingMode(vector<IntermediateFileParser::entry> *vectorToSet);
private:
	void setAddressingMode(IntermediateFileParser::entry *entryToSet);
};

#endif
