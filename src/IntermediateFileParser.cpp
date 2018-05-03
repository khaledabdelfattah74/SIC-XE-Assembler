#include "IntermediateFileParser.hpp"

IntermediateFileParser::IntermediateFileParser(string path) {
	this->path = path;
}

IntermediateFileParser::~IntermediateFileParser() {
	// TODO Auto-generated destructor stub
}

vector<IntermediateFileParser::entry> IntermediateFileParser::getEntriesVector() {
	vector<entry> entryVector;
	string line;
	ifstream intermediatefile(path);
	getline(intermediatefile, line);
	getline(intermediatefile, line);

	if (intermediatefile.is_open()) {
		while (getline(intermediatefile, line)) {
			trim(&line);
			entry e = getSuitableEntry(line);
			debugEntry(e);
			if(validEntry(e)) {
				entryVector.push_back(e);
			}
		}
		intermediatefile.close();
	}

	return entryVector;
}

void IntermediateFileParser::trim(string *strToTrim) {
	replace( strToTrim->begin(), strToTrim->end(), '\t', ' ');
	strToTrim->erase(0,9);
}

IntermediateFileParser::entry IntermediateFileParser::getSuitableEntry(string line) {
	entry newEntry;

	newEntry.address = line.substr(0, 6);
	line.erase(0, 6);

	eraseAnyForwardSpaces(&line,2);
	newEntry.label = line.substr(0, 8);
	line.erase(0, 10);

	newEntry.operationCode = line.substr(0, 8);
	line.erase(0, 10);

	string operands = line.substr(0, 17);
	line.erase(0, 18);
	extractOperands(&newEntry.operand, operands);
	return newEntry;
}

void IntermediateFileParser::eraseAnyForwardSpaces(string *str,int offset) {
	while(str->length() > 0 && str->at(0) == ' ' && offset > 0) {
		offset--;
		str->erase(0,1);
	}

}

void IntermediateFileParser::extractOperands(vector<string> *operandList,string operands) {
	int x = operands.find(',');
	if(x != operands.npos) {
		operandList->push_back(operands.substr(0, x));
		operandList->push_back(operands.substr(x + 1, operands.length()));
	} else {
		operandList->push_back(operands);
	}
}

void IntermediateFileParser::debugEntry(IntermediateFileParser::entry entryToDebug) {
	cout << entryToDebug.address;
	cout << " ";
	cout << entryToDebug.label;
	cout << " ";
	cout << entryToDebug.operationCode;
	cout << " ";
	for(int i = 0; i < entryToDebug.operand.capacity(); i++) {
		cout << entryToDebug.operand.at(i);
		cout << " ";
	}
	cout << endl;
}

bool IntermediateFileParser::validEntry(IntermediateFileParser::entry entryToValidate) {
	return entryToValidate.label.at(0) != ' ' || entryToValidate.operationCode.at(0) != ' ';
}