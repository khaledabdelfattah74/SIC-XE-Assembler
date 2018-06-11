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
	if(line[0] == '=') {
		newEntry.label = getLiteral(&line);
	} else {
		newEntry.label = line.substr(0, 8);
		removeSpaces(&newEntry.label);
		line.erase(0, 10);
	}

	newEntry.operationCode = line.substr(0, 8);
	removeSpaces(&newEntry.operationCode);

	line.erase(0, 10);
	if(line[0] == '=' || ((line[0] == 'X' || line[0]=='x') && line[1] == '\'') || ((line[0] == 'C' || line[0]=='c') && line[1] == '\''))  {
		newEntry.operand.push_back(getLiteral(&line));
	} else {
		string operands = line.substr(0, line.length());
		removeSpaces(&operands);
		extractOperands(&newEntry.operand, operands);
	}
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
	if(x != (signed)operands.npos) {
		string operand1 = operands.substr(0, x);
		string operand2 = operands.substr(x + 1, operands.length());
		removeSpaces(&operand1);
		removeSpaces(&operand2);
		operandList->push_back(operand1);
		operandList->push_back(operand2);
	} else {
		removeSpaces(&operands);
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
	for(unsigned short int i = 0; i < entryToDebug.operand.capacity(); i++) {
		cout << entryToDebug.operand.at(i);
		cout << " ";
	}
	cout << endl;
}

bool IntermediateFileParser::validEntry(IntermediateFileParser::entry entryToValidate) {
	return entryToValidate.label.at(0) != ' ' || entryToValidate.operationCode.at(0) != ' ';
}

void IntermediateFileParser::removeSpaces(string *str) {
	if(str->at(0) == ' ')
		return;
	//cout << *str << endl;
	for(auto it = str->begin();it != str->end();++it) {
		//cout << *it << endl;
		if(*it == ' ') {
			str->erase(it,it+1);
			it--;
		}
	}
	//cout << *str << endl;
}

string IntermediateFileParser::getLiteral(string *str) {
	string result;
	bool firstQoutes = false;
	int len = 0;
	for(auto it = str->begin();it != str->end();++it) {
		result.append(str->substr(len,1));
		len++;
		if(*it == '\'' && !firstQoutes) {
			firstQoutes = true;
		} else if(*it == '\'' && firstQoutes) {
			break;
		}
	}

	str->erase(0,max(len,8)+2);
	return result;
}
