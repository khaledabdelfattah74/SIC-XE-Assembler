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
string Utilities::hexWord(string word) {
	stringstream ss;
	istringstream iss(word);
	int value;
	iss >> value;
	ss << hex << value;
	string result = "000000";
	result.append(ss.str());
	return result.substr(result.length() - 6, result.length());
}
string Utilities::hexByte(string byte) {
	if (byte[0] == 'X' || byte[0] == 'x') {
		return byte.substr(2, byte.length() - 3);
	} else if (byte[0] == 'C' || byte[0] == 'c') {
		string result;

		for (auto i : byte.substr(1, byte.length())) {
			if (i != '\'') {
				stringstream ss;
				ss << hex << (int) i;
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
string Utilities::intToString(int decimal) {
	ostringstream ss;
	ss << decimal;
	return ss.str();
}
string Utilities::convertExpression(string oldExpression, unordered_map<string, string> addresses) {
	vector<string> terms { explode(oldExpression, '+', '-', '*', '/') };
	string operations[terms.size()];
	if (oldExpression.c_str()[0] == '-') {
		operations[0] = "-";
	} else {
		operations[0] = "+";
	}
	int counter = 1;
	for (int i = 1; i < oldExpression.length(); i++) {
		if (oldExpression.c_str()[i] == '-') {
			operations[counter++] = "-";
		} else if (oldExpression.c_str()[i] == '+'
				|| oldExpression.c_str()[i] == '*'
				|| oldExpression.c_str()[i] == '/') {
			operations[counter++] = oldExpression.substr(i, 1);
		}
	}
	string newExpression;
	int i = 0;
	for (auto term : terms) {
		newExpression += operations[i++];
		if(is_number(term)) {
			newExpression+=term;
			continue;
		}
		string hexaValue = addresses[term];
		int decimalValue = hexToDecimal(hexaValue);
		newExpression += intToString(decimalValue);

	}
	return newExpression;
}

string Utilities::convertExpression(string oldExpression, unordered_map<string, int> addresses) {
	vector<string> terms { explode(oldExpression, '+', '-', '*', '/') };
	string operations[terms.size()];
	if (oldExpression.c_str()[0] == '-') {
		operations[0] = "-";
	} else {
		operations[0] = "+";
	}
	int counter = 1;
	for (int i = 1; i < oldExpression.length(); i++) {
		if (oldExpression.c_str()[i] == '-') {
			operations[counter++] = "-";
		} else if (oldExpression.c_str()[i] == '+'
				|| oldExpression.c_str()[i] == '*'
				|| oldExpression.c_str()[i] == '/') {
			operations[counter++] = oldExpression.substr(i, 1);
		}
	}
	string newExpression;
	int i = 0;
	for (auto term : terms) {
		newExpression += operations[i++];
		if(is_number(term)) {
			newExpression+=term;
			continue;
		}
		newExpression += intToString(addresses[term]);
	}
	return newExpression;
}

const vector<string> Utilities::explode(const string& s, const char& c,
		const char& c1, const char& c2, const char& c3) {
	string buff { "" };
	vector<string> v;
	for (auto n : s) {
		if (n != c && n != c1 && n != c2 && n != c3)
			buff += n;
		else if ((n == c || n == c1 || n != c2 || n != c3) && buff != "") {
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "")
		v.push_back(buff);
	return v;
}

bool Utilities::is_number(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}
