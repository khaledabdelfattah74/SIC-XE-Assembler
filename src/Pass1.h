/*
 * Pass1.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef PASS1_H_
#define PASS1_H_
#include "SourceCodeTable.h"
using namespace std;

class Pass1 {
public:
	Pass1(string path);
	void mainLoop();
private:
	SourceCodeTable sourceCodeTable;
	int getLengthOf(std::string);
};

#endif /* PASS1_H_ */
