#include "AddresingModifier.h"
#include <regex>
#include <algorithm>
#include "SectionsContainer.hpp"

const regex expression ("(\\w)+(\\-|\\+)(\\w)+");

AddresingModifier::AddresingModifier() {
	// TODO Auto-generated constructor stub

}

AddresingModifier::~AddresingModifier() {
	// TODO Auto-generated destructor stub
}

void AddresingModifier::setVectorAddressingMode(vector<IntermediateFileParser::entry> *vectorToSet) {
    SectionsContainer c = SectionsContainer::get_instance();
    vector<string> ext_labels;
	for (auto it = vectorToSet->begin(); it != vectorToSet->end(); ++it) {
        if (it->operationCode == "START" || it->operationCode == "CSECT") {
            cur_sec_name = it->label;
            ext_labels = c.get_section(cur_sec_name).get_ext_ref();
        }
        if (regex_match(it->operand[0], expression)) {
            string label = "";
            for (char i = 0; i < it->operand[0].length(); i++) {
                if (it->operand[0][i] == '+' || it->operand[0][i] == '-') {
                    if (find(ext_labels.begin(), ext_labels.end(), label) != ext_labels.end()) {
                        it->need_modification_record = true;
                        it->expression_labels.push_back(label);
                    }
                    label = "";
                    continue;
                }
                label += it->operand[0][i];
            }
            if (find(ext_labels.begin(), ext_labels.end(), label) != ext_labels.end()) {
                it->need_modification_record = true;
                it->expression_labels.push_back(label);
            }
        }
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
}
