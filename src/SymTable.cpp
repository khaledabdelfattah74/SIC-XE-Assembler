/*
 * SymTable.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#include "SymTable.h"
#include <string.h>
using namespace std;
SymTable::SymTable() {
	// TODO Auto-generated constructor stub

}

SymTable::~SymTable() {
	// TODO Auto-generated destructor stub
}

void SymTable::insert(string lable, int address) {
	this->symbolTable.insert(std::make_pair<std::string,int>(lable,address));
}
bool SymTable::found(string lable) {
	if (this->symbolTable.count(lable) == 0) {
		return false;
	} else {
		return true;
	}
}
