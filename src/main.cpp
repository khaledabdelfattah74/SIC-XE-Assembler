//============================================================================
// Name        : SIC-EX-Assembler.cpp
// Author      : Sajed
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Pass1 sic assembler
//============================================================================

#include <iostream>
#include "Pass1.hpp"
#include "SicParser.hpp"
#include "SourceCodeTable.hpp"

using namespace std;

int main() {
    string path = "C:\\Users\\user\\Desktop\\test.txt";
	Pass1 pa = *new Pass1(path);
    cout << endl << "An intermediate file was written to the path: " << pa.outPath << endl;
	return 0;
}
