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
		IntermediateFileParser::entry entryToCheck = *it;
		if(entryToCheck.operationCode == "BASE" || entryToCheck.operationCode == "base"){
			canBase = true;
			string operand1 = entryToCheck.operand[0];
			if(operand1[0] == '#' || operand1[0] == '@') {
				operand1.erase(0,1);
			}
			if(operand1[0] == '*'){
				base = entryToCheck.address;
			} else {
				if(is_number(operand1)) {
					Utilities util;
					base = util.decimalToHex(util.stringToDecimal(operand1));
				}else{
					base = addresses[operand1];
				}
			}
			vectorToCalculate->erase(it,it+1);
			it--;
		} else if(entryToCheck.operationCode == "NOBASE" || entryToCheck.operationCode == "nobase") {
			canBase = false;
		} else {
			handle(&*it);
		}
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
				Utilities util;
				entryToHandle->displacemnet = util.decimalToHex(valueOfExpression(operand1));
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
		Utilities util;
		entryToHandle->displacemnet = util.decimalToHex(valueOfExpression(operand1));
	}
	return targetAdress;
}

void DisplacementCalculator::checkDisplacementOperation3(IntermediateFileParser::entry *entryToHandle,int disp,int ta) {
	string operand1 = entryToHandle->operand.at(0);
	if(addresses.count(operand1) == 0) {
		cout << "HERE";
		errorMessage += "**operand " + operand1 + " is undefined/n";
		errorMessage += getEntrySrc(*entryToHandle);
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
			errorMessage += "**displacement error\n";
			errorMessage += getEntrySrc(*entryToHandle);
			error = true;
		}
	} else {
		cout << "Error : invalid address p" << endl;
		cout << operand1 << endl;
		cout << "Error : invalid address b" << endl;
		errorMessage += "**displacement error\n";
		errorMessage += getEntrySrc(*entryToHandle);
		error = true;
	}
}

bool DisplacementCalculator::getDisplacemnetError() {
	return error;
}

int DisplacementCalculator::valueOfExpression(string expression) {
    vector<string> terms{explode(expression, '+', '-', '*', '/')};
    char operations[terms.size()];
    if (expression.c_str()[0] == '-') {
        operations[0] = '-';
    } else {
        operations[0] = '+';
    }
    int counter = 1;
    for (int i = 1; i < expression.length(); i++) {
        if (expression.c_str()[i] == '-') {
            operations[counter++] = '-';
        } else if (expression.c_str()[i] == '+' || expression.c_str()[i] == '*' || expression.c_str()[i] == '/') {
            operations[counter++] = expression.c_str()[i];
        }
    }

    int value = 0;
    int i = 0;
    for(auto term:terms) {

        int numValue = 0;
        if (term.find(',') != std::string::npos) {
            return -1;
        } else if (is_number(term)) {
            istringstream buffer(term);
            buffer >> numValue;
        } else {
            if (addresses.count(term) == 0) {
                return -2;
            }
            Utilities util;
            numValue = util.hexToDecimal(addresses[term]);
        }
        switch(operations[i]) {
            case '-' :
                value -= numValue;
                break;
            case '+' :
                value += numValue;
                break;
            case '*' :
                value *= numValue;
                break;
            case '/' :
                value /= numValue;
                break;
            default :
                cout << "Invalid operation" << endl;
        }
        i++;
    }
    return value;

}

bool DisplacementCalculator::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

const vector<string> DisplacementCalculator::explode(const string& s, const char& c, const char& c1, const char& c2, const char& c3) {
    string buff{""};
    vector<string> v;
    for(auto n:s) {
        if(n != c && n!= c1 && n!= c2 && n!= c3) buff+=n; else
        if((n == c || n ==c1 || n!= c2 || n!= c3) && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);
    return v;
}

string DisplacementCalculator::getEntrySrc(IntermediateFileParser::entry entry) {
	string result;
	result += entry.address + " " + entry.operationCode + " ";
	for(int i = 0;i < entry.operand.size();i++) {
		result += entry.operand[i] + ",";
	}
	result.erase(result.length() - 1,1);
	result += "\n";
	return result;
}
string DisplacementCalculator::getErrorMessage() {
	return errorMessage;
}
