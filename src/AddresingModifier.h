#ifndef SRC_ADDRESINGMODIFIER_H_
#define SRC_ADDRESINGMODIFIER_H_

#include "IntermediateFileParser.hpp"
#include "ControlSection.hpp"
#include <unordered_map>

class AddresingModifier {
public:
	AddresingModifier();
	virtual ~AddresingModifier();
	void setVectorAddressingMode(vector<IntermediateFileParser::entry> *vectorToSet,
                                 unordered_map<string, ControlSection>);
private:
	void setAddressingMode(IntermediateFileParser::entry *entryToSet);
    string cur_sec_name;
};

#endif
