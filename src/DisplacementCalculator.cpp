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
		string operand1;
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
			if(entryToHandle->displacemnet.length() != 0)
				return;
			disp = ta - pc;
			checkDisplacementOperation3(entryToHandle, disp, ta);
			break;
		case 4:
			cout << 4 << endl;
			if(entryToHandle->operand.capacity() == 0) {
				cout << "Error : no operand or may be +RSUB";
				return;
			}
			operand1 = entryToHandle->operand.at(0);
			if(operand1.at(0) == '@' || operand1.at(0) == '#') {
				operand1.erase(0,1);
			}
			if((operand1.find('-')  == operand1.npos || operand1[0]  == '-' || operand1[0]  == '=') && operand1.find('+') == operand1.npos) {
				if(addresses.count(operand1) > 0) {
					ss << hex << addresses[operand1];
					entryToHandle->displacemnet = ss.str();
				}
				if(isdigit(operand1.at(0)) || operand1.at(0) == '-'){
					istringstream iss(operand1);
					int value;
					iss >> value;
					ss << hex << value;
					entryToHandle->displacemnet = ss.str();
					return;
				}
				if(addresses.count(operand1) == 0) {
					error = true;
				}
			} else {

			}
			break;
		default:
			cout << "Displacement Error or  directive" << endl;
		}
	}

}
int DisplacementCalculator::handleOperation3(IntermediateFileParser::entry *entryToHandle) {
	if(entryToHandle->operand.capacity() == 0) {
		cout << "Error : no operand or may be RSUB";
		return 0;
	}
	int targetAdress = 0;
	string operand1 = entryToHandle->operand.at(0);
	if(operand1.at(0) == '@' || operand1.at(0) == '#') {
		operand1.erase(0,1);
	}

	if((operand1.find('-')  == operand1.npos || operand1[0]  == '-' || operand1[0]  == '=') && operand1.find('+') == operand1.npos) {
		stringstream ss;
		if(addresses.count(operand1) > 0) {
			ss << hex << addresses[operand1];
			ss >> targetAdress;
		}
		if (isdigit(operand1.at(0)) || operand1[0]  == '-') {
			istringstream iss(operand1);
			int value;
			iss >> value;
			ss << hex << value;
			entryToHandle->displacemnet = ss.str();
		}
	} else {
		//TO DO handle expression bonus
	}
	return targetAdress;
}

void DisplacementCalculator::checkDisplacementOperation3(IntermediateFileParser::entry *entryToHandle,int disp,int ta) {
	string operand1 = entryToHandle->operand.at(0);
	if(addresses.count(operand1) == 0) {
		cout << "HERE";
		error = true;
	}
	cout << addresses[operand1]<<endl;
	cout << disp << endl;
	if(operand1.at(0) == '@' || operand1.at(0) == '#') {
			operand1.erase(0,1);
	}
	if(-2048 <= disp && disp <= 2047 && addresses.count(operand1) > 0) {
		stringstream ss;
		ss << hex << disp;
		cout << entryToHandle-> address << " : "<< entryToHandle->operand.at(0) << " : " << ss.str() << " : " << disp;
		entryToHandle->displacemnet = ss.str();
		entryToHandle->p = 1;
	} else if(canBase && disp > 0 && addresses.count(operand1) > 0) {
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
		cout << operand1 << endl;
	}
}

bool DisplacementCalculator::getDisplacemnetError() {
	return error;
}
