/*
 * Utilities.h
 *
 *  Created on:
 *      Author: ecc
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;
class Utilities {
public:
	Utilities();
	virtual ~Utilities();
	string hexWord(string word);
	string hexByte(string byte);
	string decimalToHex(int decimal);
	int hexToDecimal(string hex);
	string convertExpression(string oldExpression,unordered_map<string,string> addresses);
	string intToString(int decimal);
	string convertExpression(string oldExpression,unordered_map<string,int> addresses);
	const vector<string> explode(const string& s, const char& c, const char& c1, const char& c2, const char& c3);
	bool is_number(const std::string& s);
	int valueOfExpression(string expression);
};

#endif /* SRC_UTILITIES_H_ */
