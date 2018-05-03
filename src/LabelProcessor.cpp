#include "LabelProcessor.h"

LabelProcessor::LabelProcessor() {
	// TODO Auto-generated constructor stub

}

LabelProcessor::~LabelProcessor() {
	// TODO Auto-generated destructor stub
}

unordered_map<string,string> LabelProcessor::assignLabelAddresses(vector<IntermediateFileParser::entry> vectorToProcess) {
	unordered_map<string,string> labelAdresses;
	for(short int i = 0;i < vectorToProcess.capacity();i++) {
		IntermediateFileParser::entry entryToProcess = vectorToProcess.at(i);
		if(entryToProcess.label.at(0) != ' ') {
			if(labelAdresses.count(entryToProcess.label) == 0) {
				labelAdresses.insert(make_pair(entryToProcess.label,entryToProcess.address));
			} else {
				errorFlag = true;
			}
		}
	}
	return labelAdresses;
}

bool LabelProcessor::getErrorFlag() {
	return errorFlag;
}
