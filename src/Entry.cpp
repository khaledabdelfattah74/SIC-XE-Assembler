/*
 * Entry.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#include "Entry.h"

Entry::Entry(string lable, string opCode, string operand, string comment, bool commentLine) {
	this->lable = lable;
	this->opCode = opCode;
	this->operand = operand;
	this->comment = comment;
	this->commentLine = commentLine;
}

string Entry::getLable() {
	return this->lable;
}

string Entry::getOpCode() {
	return this->opCode;
}

string Entry::getOperand() {
	return this->operand;
}

string Entry::getComment() {
	return this->comment;
}

bool Entry::isCommentLine() {
	return this->commentLine;
}

