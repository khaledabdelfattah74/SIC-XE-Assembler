#ifndef SRC_DISPLACEMENTCALCULATOR_H_
#define SRC_DISPLACEMENTCALCULATOR_H_

#include "IntermediateFileParser.hpp"
#include "OpTable.hpp"

class DisplacementCalculator {
public:
	DisplacementCalculator(unordered_map<string,string> labelAddresses);
	virtual ~DisplacementCalculator();
	void handleDisplacement(vector<IntermediateFileParser::entry> *vectorToCalculate);
	bool getDisplacemnetError();
private:
	string base = "";
	bool canBase = false;
	bool error = false;
	OpTable operations;
	unordered_map<string,string> addresses;
	void handle(IntermediateFileParser::entry *entryToHandle);
	int handleOperation3(IntermediateFileParser::entry *entryToHandle);
	void checkDisplacementOperation3(IntermediateFileParser::entry *entryToHandle,int disp, int ta);
};

#endif
