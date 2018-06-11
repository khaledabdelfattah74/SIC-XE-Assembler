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
    string cur_sec_name;
    vector<string> ext_labels;
};

#endif
