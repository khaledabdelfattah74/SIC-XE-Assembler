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
#include "DisplacementCalculator.h"
#include "OpTable.hpp"
#include "Utilities.h"
#include "ObjectProgramGenerator.h"
#include "Pass2.h"

using namespace std;

Pass2::Pass2() {
}

Pass2::~Pass2() {

}

void Pass2::debugEntriesVectors(vector<IntermediateFileParser::entry> vectorToDebug) {
	cout << endl;
	cout <<"Entries Of Vector"<< endl;
	cout << endl;
	for(unsigned short int i = 0;i < vectorToDebug.capacity();i++) {
		IntermediateFileParser::entry entryToDebug = vectorToDebug.at(i);
		cout << entryToDebug.address;
		cout << " ";
		cout << entryToDebug.label;
		cout << " ";
		cout << entryToDebug.operationCode;
		cout << " ";
		for(unsigned short int j = 0; j < entryToDebug.operand.capacity(); j++) {
			cout << entryToDebug.operand.at(j);
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Pass2::debugLabelAddresses(unordered_map<string,string> addresses) {
	cout << endl;
	cout <<"Label Addresses"<< endl;
	cout << endl;
	for ( auto it = addresses.begin(); it != addresses.end(); ++it ) {
	    cout << it->first << ":" << it->second;
		cout << endl;
	}
	cout << endl;
}

void Pass2::debugAddressMode(vector<IntermediateFileParser::entry> vectorToDebug) {
	cout << endl;
	cout<<"Address Mode"<<endl;
	cout << endl;
	for(unsigned short int i = 0;i < vectorToDebug.capacity();i++) {
			IntermediateFileParser::entry entryToDebug = vectorToDebug.at(i);
			cout << entryToDebug.address;
			cout << " ";
			cout << entryToDebug.label;
			cout << " ";
			cout << entryToDebug.operationCode;
			cout << " ";
			for(unsigned short int j = 0; j < entryToDebug.operand.capacity(); j++) {
				cout << entryToDebug.operand.at(j);
				cout << " ";
			}
			cout << entryToDebug.getAddressingMode();
			cout << endl;
		}
	cout << endl;
}
void Pass2::debugDisplacement(vector<IntermediateFileParser::entry> vectorToDebug) {
	OpTable x;
	cout << endl;
	cout<<"Displacement"<<endl;
	cout << endl;
	for(unsigned short int i = 0;i < vectorToDebug.capacity();i++) {
			IntermediateFileParser::entry entryToDebug = vectorToDebug.at(i);
			cout << i << " -";
			cout << entryToDebug.address;
			cout << " ";
			cout << entryToDebug.label;
			cout << " ";
			cout << entryToDebug.operationCode;
			cout << " ";
			for(unsigned short int j = 0; j < entryToDebug.operand.capacity(); j++) {
				cout << entryToDebug.operand.at(j);
				cout << " ";
			}
			cout << " " << x.getOperationCode(entryToDebug.operationCode) << " ";
			cout << entryToDebug.getAddressingMode();
			cout << " " << entryToDebug.displacemnet;
			cout << endl;
		}
	cout << endl;
}
void Pass2::debugUtilities() {
	Utilities x = *new Utilities();
	cout << endl;
	cout << "Utilities : "<< endl;
	cout << "HexWord : 15 >>> " + x.hexWord("15") << endl;
	cout << "HexByte : c'abcABC' >>> " + x.hexByte("C'abcABC'") << endl;
	cout << "HexByte : X'af00' >>> " + x.hexByte("X'af00'") << endl;
	cout << "DecimalToHex : 10 >>> " + x.decimalToHex(10) << endl;
	cout << "HexToDecimal : aaf >> " << x.hexToDecimal("aaf") << endl;
	unordered_map<string,string> map = {
			{"hexa","a"},
			{"input","b"},
			{"savew","c"}
	};
	cout << "Convert Expression(hexa-input+savew*10/hexa) : >>>" << x.convertExpression("hexa-input+savew*10/hexa", map)<<endl;

	unordered_map<string,int> map2 = {
				{"hexa",10},
				{"input",11},
				{"savew",12}
		};
	cout << "Convert Expression(10-20+30*2/10) : >>>" << x.convertExpression("10-20+30*2/10", map2)<<endl;

}

int Pass2::excute(string outPath) {

	IntermediateFileParser intermediateParser = *new IntermediateFileParser(outPath);
	vector<IntermediateFileParser::entry> allEntryVector = intermediateParser.getEntriesVector();
	cout << allEntryVector.size() << endl;
	LabelProcessor labelProcessor = *new LabelProcessor();
	unordered_map<string,string> labelAddresses = labelProcessor.assignLabelAddresses(&allEntryVector);
	/*if(labelProcessor.getErrorFlag()) {
		cout << "uncompletely assembled";
		return 0;
	}*/
	debugUtilities();
	AddresingModifier addressModifier = *new AddresingModifier();
	addressModifier.setVectorAddressingMode(&allEntryVector);

	DisplacementCalculator disCalc = *new DisplacementCalculator(labelAddresses);
	cout << "HERE "<<labelAddresses["=W'-152'"]<<endl;
	disCalc.handleDisplacement(&allEntryVector);
	debugDisplacement(allEntryVector);
	if(disCalc.getDisplacemnetError()) {
		cout << "uncompletely assembled\n";
		errorMessage = disCalc.getErrorMessage();
		return 0;
	}
	//debugLabelAddresses(labelAddresses);
	//debugEntriesVectors(allEntryVector);
	//debugAddressMode(allEntryVector);

	ObjectProgramGenerator objGen = *new ObjectProgramGenerator();
	objGen.generate_program_code(allEntryVector);
	return 1;
}

string Pass2::getErrorMessage() {
	return errorMessage;
}
