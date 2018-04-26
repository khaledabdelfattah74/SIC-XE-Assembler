/*
 * OpTable.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef OPTABLE_H_
#define OPTABLE_H_
#include <string>
#include <unordered_map>

using namespace std;

class OpTable {
public:
	OpTable();
	virtual ~OpTable();
	bool found(std::string);
	int lengthOf(std::string);
private:
	unordered_map<string, int> operationTable;
};

#endif /* OPTABLE_H_ */
