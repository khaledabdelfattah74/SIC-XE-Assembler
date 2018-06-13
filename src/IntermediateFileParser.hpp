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
			int n = 0;
			int i = 0;
			int x = 0;
			int b = 0;
			int p = 0;
			int e = 0;
			string displacemnet = "";
			bool isAbs;
            bool need_modification_record = false;
            vector<pair<string, char>> expression_labels;
			string getAddressingMode() {
				string mode = to_string(n) + to_string(i)+to_string(x)+to_string(b)+to_string(p)+to_string(e);
				return mode;
			}
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
	void removeSpaces(string *str);
	void debugEntry(entry entryToDebug);
	bool validEntry(entry entryToValidate);
	string getLiteral(string *str);

};

#endif
