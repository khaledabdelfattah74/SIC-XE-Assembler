//============================================================================
// Name        : Pass2.cpp
// Author      : bassam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "IntermediateFileParser.hpp"
using namespace std;

void debugEntriesVectors(vector<IntermediateFileParser::entry> vectorToDebug) {
	for(int i = 0;i < vectorToDebug.capacity();i++) {
		IntermediateFileParser::entry entryToDebug = vectorToDebug.at(i);
		cout << entryToDebug.address;
		cout << " ";
		cout << entryToDebug.label;
		cout << " ";
		cout << entryToDebug.operationCode;
		cout << " ";
		for(int j = 0; j < entryToDebug.operand.capacity(); j++) {
			cout << entryToDebug.operand.at(j);
			cout << " ";
		}
		cout << endl;
	}
}

int main() {

	IntermediateFileParser x = *new IntermediateFileParser("C:\\FPC\\prog\\srcfileOut.txt");
	vector<IntermediateFileParser::entry> y = x.getEntriesVector();
	debugEntriesVectors(y);
	return 0;//
}


