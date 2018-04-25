/*
 * SymTable.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef SYMTABLE_H_
#define SYMTABLE_H_
#include <string.h>
#include <unordered_map>


class SymTable {
public:
	SymTable();
	virtual ~SymTable();
	void insert(std::string, int);
	bool found(std::string);
private:
	std::tr1::unordered_map<std::string, int> symbolTable;
};
#endif /* SYMTABLE_H_ */
