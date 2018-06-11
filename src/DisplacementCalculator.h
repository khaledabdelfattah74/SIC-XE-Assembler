#ifndef SRC_DISPLACEMENTCALCULATOR_H_
#define SRC_DISPLACEMENTCALCULATOR_H_

#include "IntermediateFileParser.hpp"
#include "OpTable.hpp"
#include "Utilities.h"
class DisplacementCalculator {
public:
	DisplacementCalculator(unordered_map<string,string> labelAddresses);
	virtual ~DisplacementCalculator();
	void handleDisplacement(vector<IntermediateFileParser::entry> *vectorToCalculate);
	bool getDisplacemnetError();
	string getErrorMessage();
private:
	string base = "";
	string errorMessage;
	bool canBase = false;
	bool error = false;
	OpTable operations;
	unordered_map<string,string> addresses;
	void handle(IntermediateFileParser::entry *entryToHandle);
	int handleOperation3(IntermediateFileParser::entry *entryToHandle);
	void checkDisplacementOperation3(IntermediateFileParser::entry *entryToHandle,int disp, int ta);
	int valueOfExpression(string expression);

	bool is_number(const std::string& s);

	const vector<string> explode(const string& s, const char& c, const char& c1, const char& c2, const char& c3);
	string getEntrySrc(IntermediateFileParser::entry entry);
};

#endif
