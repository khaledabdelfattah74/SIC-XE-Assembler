/*
 * Utilities.cpp
 *      Author: ecc
 */

#include "Utilities.h"

Utilities::Utilities() {
	// TODO Auto-generated constructor stub

}

Utilities::~Utilities() {
	// TODO Auto-generated destructor stub
}
string Utilities::hexWord(string word)
{
	stringstream ss;
	istringstream iss(word);
	int value;
	iss >> value;
	ss << hex << value;
	string result = "000000";
	result.append(ss.str());
	return result.substr(result.length() - 6, result.length());
}
string Utilities::hexByte(string byte)
{
	if(byte[0] == 'X' || byte[0] == 'x') {
		return byte.substr(2, byte.length() - 3);
	} else if(byte[0] == 'C' || byte[0] == 'c') {
		string result;

		for(auto i : byte.substr(1, byte.length())) {
			if(i != '\'') {
				stringstream ss;
				ss << hex <<(int)i;
				result += ss.str();
			}
		}
		return result;
	}
	return "INVALID BYTE FORMAT !!";
}

string Utilities::decimalToHex(int decimal) {
	string result = "000000";
	stringstream ss;
	ss << hex << decimal;
	result.append(ss.str());
	return result.substr(result.length() - 6, result.length());
}

int Utilities::hexToDecimal(string hexa) {
	int result;
	stringstream ss;
	ss << hex << hexa;
	ss >> result;
	return result;
}
