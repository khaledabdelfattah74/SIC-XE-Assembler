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

using namespace std;
class Utilities {
public:
	Utilities();
	virtual ~Utilities();
	string hexWord(string word);
	string hexByte(string byte);
	string decimalToHex(int decimal);
	int hexToDecimal(string hex);
};

#endif /* SRC_UTILITIES_H_ */
