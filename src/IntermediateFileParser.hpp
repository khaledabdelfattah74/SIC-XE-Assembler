#ifndef INTERMEDIATEFILEPARSER_HPP_
#define INTERMEDIATEFILEPARSER_HPP_

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class IntermediateFileParser {

public:
	struct entry {
			string address;
			string label;
			string operationCode;
			vector<string> operand;
		};
	IntermediateFileParser(string path);
	virtual ~IntermediateFileParser();
	vector<entry> getEntriesVector();
private:
	string path;
	void trim(string *strToTrim);
	entry getSuitableEntry(string line);
	void eraseAnyForwardSpaces(string *str,int offset);
	void extractOperands(vector<string> *operandList,string operands);
	void debugEntry(entry entryToDebug);
	bool validEntry(entry entryToValidate);

};

#endif /* INTERMEDIATEFILEPARSER_HPP_ */
