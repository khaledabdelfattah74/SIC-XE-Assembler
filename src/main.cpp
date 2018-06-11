//
//  main.cpp
//  SIC-XE-Assembler
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "SicParser.hpp"
#include "SourceCodeTable.hpp"
#include "Entry.hpp"
#include "Pass1.hpp"
#include "Validator.hpp"

using namespace std;


/*int main(int argc, const char * argv[]) {
    //Validator v = *new Validator();
    //cout << v.check_vaidity("LDA", "=X'123'") << endl;
    //cout << regex_match("A,X", twoRegesters) << endl;
    string path = "/home/sajed/CLionProjects/untitled/test.txt";
    Pass1 pass(path);
    cout << endl << "An intermediate file was written to the path: " << pass.outPath << endl;
/*int main(int argc, const char * argv[]) {
    Validator v = *new Validator();
    //cout << v.check_vaidity("LDA", "=X'123'") << endl;

    //cout << regex_match("A,X", twoRegesters) << endl;

    string path = "C:\\FPC\\prog\\srcfile.txt";
    Pass1 pass = *new Pass1(path);
    cout << endl << "An intermediate file was written to the path: " << pass.outPath << endl;

    /*SicParser parser = * new SicParser();
    SourceCodeTable table = parser.parse(path);
    Entry entry = *table.fetchNextEntry();
    cout << entry.getLable() << " " << entry.getOpCode() << " " << entry.getOperand() << " " << entry.getComment() << endl;*/
/*  return 0;
 */
/*}*/

