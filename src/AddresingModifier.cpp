#include "AddresingModifier.h"

AddresingModifier::AddresingModifier() {
	// TODO Auto-generated constructor stub

}

AddresingModifier::~AddresingModifier() {
	// TODO Auto-generated destructor stub
}

void AddresingModifier::setVectorAddressingMode(vector<IntermediateFileParser::entry> *vectorToSet) {
	for (auto it = vectorToSet->begin(); it != vectorToSet->end(); ++it) {
		setAddressingMode(&*it);
	}
}
void AddresingModifier::setAddressingMode(IntermediateFileParser::entry *entryToSet) {
	if (entryToSet->operationCode.at(0) == '+') {
		entryToSet->e = 1;
		if (entryToSet->operand.capacity() == 1) {
			entryToSet->x = 0;
			if (entryToSet->operand.at(0).at(0) == '@') {
				entryToSet->n = 1;
				entryToSet->i = 0;
			} else if (entryToSet->operand.at(0).at(0) == '#') {
				entryToSet->n = 0;
				entryToSet->i = 1;
			} else {
				entryToSet->n = 1;
				entryToSet->i = 1;
			}
		} else if (entryToSet->operand.capacity() == 2) {
			entryToSet->x = 1;
			entryToSet->n = 1;
			entryToSet->i = 1;
		}
	} else {
		entryToSet->e = 0;
		if (entryToSet->operand.capacity() == 1) {
			if (entryToSet->operand.at(0).at(0) == '@') {
				entryToSet->n = 1;
				entryToSet->i = 0;
			} else if (entryToSet->operand.at(0).at(0) == '#') {
				entryToSet->n = 0;
				entryToSet->i = 1;
			} else {
				entryToSet->n = 1;
				entryToSet->i = 1;
			}
		} else if (entryToSet->operand.capacity() == 2) {
			entryToSet->x = 1;
			entryToSet->n = 1;
			entryToSet->i = 1;
		}
	}
	//cout<< entryToSet->getAddressingMode()<<endl;
}
