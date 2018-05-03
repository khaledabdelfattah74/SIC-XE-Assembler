#ifndef SRC_DISPLACEMENTCALCULATOR_H_
#define SRC_DISPLACEMENTCALCULATOR_H_

#include "IntermediateFileParser.hpp"
#include "OpTable.hpp"

class DisplacementCalculator {
public:
	DisplacementCalculator();
	virtual ~DisplacementCalculator();
	void handleDisplacement(vector<IntermediateFileParser::entry> *vectorToCalculate);
private:
	string base = "";
	bool canBase = false;
	OpTable operations;
	void handle(IntermediateFileParser::entry *entryToHandle);
};

#endif
