#include "DisplacementCalculator.h"
#include <iostream>
#include <sstream>
DisplacementCalculator::DisplacementCalculator(unordered_map<string,string> labelAddresses) {
	addresses = labelAddresses;
}

DisplacementCalculator::~DisplacementCalculator() {
	// TODO Auto-generated destructor stub
}

void DisplacementCalculator::handleDisplacement(
		vector<IntermediateFileParser::entry> *vectorToCalculate) {
	for (auto it = vectorToCalculate->begin(); it != vectorToCalculate->end();
			++it) {
		handle(&*it);
	}
}

void DisplacementCalculator::handle(IntermediateFileParser::entry *entryToHandle) {
	/**
	 * handle b p indictors
	 * handle displacement
	 * handle base directive
	 *
	 */

	if (operations.found(entryToHandle->operationCode)) {
		string progCounter = entryToHandle->address;
		stringstream ss;
		int pc,disp,ta;
		switch (operations.lengthOf(entryToHandle->operationCode)) {
		case 1:
			cout << 1 << endl;
			//what to do here XD
			break;
		case 2:
			cout << 2 << endl;
			//no displacement here
			break;
		case 3:
			cout << 3 << endl;
			ss << hex << progCounter;
			ss >> pc;
			pc += 3;
			//get operand addresses then disp = TA - PC
			ta = handleOperation3(entryToHandle);
			disp = ta - pc;
			checkDisplacementOperation3(entryToHandle, disp, ta);
			break;
		case 4:
			cout << 4 << endl;
			break;
		default:
			cout << "Displacement Error or  directive" << endl;
		}
	}

}
int DisplacementCalculator::handleOperation3(IntermediateFileParser::entry *entryToHandle) {
	if(entryToHandle->operand.capacity() == 0) {
		cout << "Error : no operand Or May be RSUB";
		return 0;
	}
	int targetAdress = 0;
	string operand1 = entryToHandle->operand.at(0);
	if(operand1.find('-')  == operand1.npos && operand1.find('+') == operand1.npos) {
		if(addresses.count(operand1) > 0) {
			stringstream ss;
			ss << hex << addresses[operand1];
			ss >> targetAdress;
		} else {
			//for constant values or undefined labels
		}
	} else {
		//TO DO handle expression bonus
	}
	return targetAdress;
}

void DisplacementCalculator::checkDisplacementOperation3(IntermediateFileParser::entry *entryToHandle,int disp,int ta) {
	if(-2048 <= disp && disp <= 2047 && addresses.count(entryToHandle->operand.at(0)) > 0) {
		stringstream ss;
		ss << hex << disp;
		cout << entryToHandle-> address << " : "<< entryToHandle->operand.at(0) << " : " << ss.str() << " : " << disp;
		entryToHandle->displacemnet = ss.str();
		entryToHandle->p = 1;
	} else if(canBase && disp > 0 && addresses.count(entryToHandle->operand.at(0)) > 0) {
		stringstream ss;
		int b = 0;
		ss << hex << base;
		ss >> b;
		disp = ta - b;
		if(disp >= 0 && disp <= 4095) {
			ss << hex << disp;
			cout << ss.str() <<" : "<< disp;
			entryToHandle->displacemnet = ss.str();
			entryToHandle->b = 1;
		} else {
			cout << "Error : invalid address b" << endl;
		}
	} else {
		cout << "Error : invalid address p" << endl;
	}
}
