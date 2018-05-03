#include "DisplacementCalculator.h"

DisplacementCalculator::DisplacementCalculator() {
	// TODO Auto-generated constructor stub

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
		switch (operations.lengthOf(entryToHandle->operationCode)) {
		case 1:
			cout << 1 << endl;

			break;
		case 2:
			cout << 2 << endl;
			break;
		case 3:
			cout << 3 << endl;
			break;
		case 4:
			cout << 4 << endl;
			break;
		default:
			cout << "Displacement Error or  directive"<<endl;
		}
	}
}
