/*
 * OpTable.h
 *
 *  Created on: Apr 25, 2018
 *      Author: user
 */

#ifndef OPTABLE_H_
#define OPTABLE_H_

class OpTable {
public:
	OpTable();
	virtual ~OpTable();
	bool found(std::string);
	int lengthOf(std::string);
private:
	std::tr1::unordered_map<std::string, int> operationTable;
};

#endif /* OPTABLE_H_ */
