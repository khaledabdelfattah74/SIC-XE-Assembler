/*
 * SymTable.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef SYMTABLE_H_
#define SYMTABLE_H_
#include <string>
#include <unordered_map>

using namespace std;

class SymTable {
public:
	SymTable();
	virtual ~SymTable();
	void insert(string, int);
	bool found(string);
private:
	unordered_map<string, int> symbolTable;
};
#endif /* SYMTABLE_H_ */
