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
#include "AddresingModifier.h"

using namespace std;

void debugEntriesVectors(vector<IntermediateFileParser::entry> vectorToDebug) {
	cout << endl;
	cout <<"Entries Of Vector"<< endl;
	cout << endl;
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
	cout << endl;
}

void debugLabelAddresses(unordered_map<string,string> addresses) {
	cout << endl;
	cout <<"Label Addresses"<< endl;
	cout << endl;
	for ( auto it = addresses.begin(); it != addresses.end(); ++it ) {
	    cout << it->first << ":" << it->second;
		cout << endl;
	}
	cout << endl;
}

void debugAddressMode(vector<IntermediateFileParser::entry> vectorToDebug) {
	cout << endl;
	cout<<"Address Mode"<<endl;
	cout << endl;
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
			cout << entryToDebug.getAddressingMode();
			cout << endl;
		}
	cout << endl;
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
	AddresingModifier addressModifier = *new AddresingModifier();
	addressModifier.setVectorAddressingMode(&allEntryVector);

	debugLabelAddresses(labelAddresses);
	debugEntriesVectors(allEntryVector);
	debugAddressMode(allEntryVector);
	return 0;
}

