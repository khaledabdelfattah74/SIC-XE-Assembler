/*
 * Entry.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef ENTRY_H_
#define ENTRY_H_
#include<string>
using namespace std;
class Entry {
public:
	Entry(string lable, string opCode, string operand, string comment, bool isCommentLine);
	string getLable();
	string getOpCode();
	string getOperand();
	string getComment();
	bool isCommentLine();
private:
	string lable;
	string opCode;
	string operand;
	string comment;
	bool commentLine;
};

#endif /* ENTRY_H_ */
