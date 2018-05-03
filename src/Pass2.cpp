//============================================================================
// Name        : Pass2.cpp
// Author      : bassam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "IntermediateFileParser.hpp"
#include "LabelProcessor.h"
using namespace std;

void debugEntriesVectors(vector<IntermediateFileParser::entry> vectorToDebug) {
	for(short int i = 0;i < vectorToDebug.capacity();i++) {
		IntermediateFileParser::entry entryToDebug = vectorToDebug.at(i);
		cout << entryToDebug.address;
		cout << " ";
		cout << entryToDebug.label;
		cout << " ";
		cout << entryToDebug.operationCode;
		cout << " ";
		for(short int j = 0; j < entryToDebug.operand.capacity(); j++) {
			cout << entryToDebug.operand.at(j);
			cout << " ";
		}
		cout << endl;
	}
}

void debugLabelAddresses(unordered_map<string,string> addresses) {
	for ( auto it = addresses.begin(); it != addresses.end(); ++it ) {
	    cout << it->first << ":" << it->second;
		cout << endl;
	}
}
int main() {

	IntermediateFileParser intermediateParser = *new IntermediateFileParser("C:\\FPC\\prog\\srcfileOut.txt");
	vector<IntermediateFileParser::entry> allEntryVector = intermediateParser.getEntriesVector();
	LabelProcessor labelProcessor = *new LabelProcessor();
	unordered_map<string,string> labelAddresses = labelProcessor.assignLabelAddresses(&allEntryVector);
	if(labelProcessor.getErrorFlag()) {
		cout << "uncompletely assembled";
		return 0;
	}
	//debugLabelAddresses(labelAddresses);
	debugEntriesVectors(allEntryVector);
	return 0;
}


