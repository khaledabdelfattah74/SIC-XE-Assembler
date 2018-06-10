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
#include "Pass1.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    string path = "/home/sajed/CLionProjects/untitled/test.txt";
    Pass1 pass(path);
    cout << endl << "An intermediate file was written to the path: " << pass.outPath << endl;
    return 0;
}
