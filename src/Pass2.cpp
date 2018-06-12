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
#include "SicParser.hpp"

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

vector<ControlSection> Pass2::get_sections(vector<IntermediateFileParser::entry> enteries) {
    vector<ControlSection> sections;
    string sec_name;
    vector<IntermediateFileParser::entry> sec_entries;
    vector<string> ext_ref, ext_def;
    for (IntermediateFileParser::entry entry : enteries) {
        if (entry.operationCode == "START") {
            sec_name = entry.label;
        }
        if (entry.operationCode == "CSECT") {
            ControlSection section = *new ControlSection();
            section.sec_name = sec_name;
            section.entries = sec_entries;
            section.ext_ref = ext_ref;
            section.ext_def = ext_def;
            sections.push_back(section);
            sec_name = entry.label;
            sec_entries.clear();
            ext_def.clear();
            ext_ref.clear();
        }
        if (entry.operationCode == "EXTREF") {
            //ext_ref.insert(ext_ref.end(), entry.operand.begin(), entry.operand.end());
            ext_ref = entry.operand;
        }
        if (entry.operationCode == "EXTDEF") {
            //ext_ref.insert(ext_def.end(), entry.operand.begin(), entry.operand.end());
            ext_def = entry.operand;
        }
        sec_entries.push_back(entry);
        if (entry.operationCode == "END") {
            ControlSection section = *new ControlSection();
            section.sec_name = sec_name;
            section.entries = sec_entries;
            section.ext_ref = ext_ref;
            section.ext_def = ext_def;
            sections.push_back(section);
            sec_name = entry.label;
            sec_entries.clear();
            ext_def.clear();
            ext_ref.clear();
        }
    }
    return sections;
}


int Pass2::excute(string outPath, string objectCodePath) {

	IntermediateFileParser intermediateParser = *new IntermediateFileParser(outPath);
	vector<IntermediateFileParser::entry> allEntryVector = intermediateParser.getEntriesVector();

    vector<ControlSection> sections  = get_sections(allEntryVector);
    unordered_map<string, ControlSection> container;
    for (ControlSection c : sections)
        container[c.sec_name] = c;
    
    cout << allEntryVector.size() << endl;
	LabelProcessor labelProcessor = *new LabelProcessor();
	unordered_map<string,string> labelAddresses = labelProcessor.assignLabelAddresses(&allEntryVector);
    
    debugUtilities();
	AddresingModifier addressModifier = *new AddresingModifier();
	addressModifier.setVectorAddressingMode(&allEntryVector, container);
    
    sections.clear();
    sections  = get_sections(allEntryVector);
    container.clear();
    for (ControlSection c : sections)
        container[c.sec_name] = c;

    
	DisplacementCalculator disCalc = *new DisplacementCalculator(labelAddresses);
	cout << "HERE "<<labelAddresses["=W'-152'"]<<endl;
	disCalc.handleDisplacement(&allEntryVector);
	debugDisplacement(allEntryVector);
	if(disCalc.getDisplacemnetError()) {
		cout << "incompletely assembled\n";
		errorMessage = disCalc.getErrorMessage();
		return 0;
	}
    
    cout << sections[0].get_enteries()[sections[0].get_enteries().size() - 1].operationCode << "is need "
    << allEntryVector[allEntryVector.size() - 2].expression_labels.size()
    << " " << sections[1].get_enteries()[sections[1].get_enteries().size() - 1].operationCode << endl;
    
    
    string object_code = "";
	ObjectProgramGenerator objGen = *new ObjectProgramGenerator(labelAddresses, container, objectCodePath);
    for (ControlSection section : sections)
        object_code += objGen.generate_program_code(section.get_enteries());
    object_code = SicParser::to_upper(object_code);
    objGen.write_string_to_file(object_code, objectCodePath);

	return 1;
}

string Pass2::getErrorMessage() {
	return errorMessage;
}
