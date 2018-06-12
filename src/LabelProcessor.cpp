#include "LabelProcessor.h"

LabelProcessor::LabelProcessor() {
	// TODO Auto-generated constructor stub

}

LabelProcessor::~LabelProcessor() {
	// TODO Auto-generated destructor stub
}

unordered_map<string,string> LabelProcessor::assignLabelAddresses(vector<IntermediateFileParser::entry> *vectorToProcess) {
	unordered_map<string,string> labelAdresses;
	for ( auto it = vectorToProcess->begin(); it != vectorToProcess->end(); ++it ) {
		IntermediateFileParser::entry entryToProcess = *it;
				if(entryToProcess.label.at(0) != ' ') {
					if(labelAdresses.count(entryToProcess.label) == 0) {
						labelAdresses.insert(make_pair(entryToProcess.label,entryToProcess.address));
						if(canBeRemved(entryToProcess)) {
							vectorToProcess->erase(it,it+1);
							it--;
						}
					} else {
						errorFlag = true;
					}
				} else {
					if(canBeRemved(entryToProcess)) {
						vectorToProcess->erase(it,it+1);
						it--;
					}
				}
		}
	return labelAdresses;
}

bool LabelProcessor::getErrorFlag() {
	return errorFlag;
}

bool LabelProcessor::canBeRemved(IntermediateFileParser::entry entryToCheck) {
	bool op1 = false;
	string operation = entryToCheck.operationCode;
	op1 = operation.find("res") != operation.npos || operation.find("RES") != operation.npos;
	return op1;
}
