//
//  Pass1.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 4/26/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef Pass1_hpp
#define Pass1_hpp

#include <stdio.h>

#include "SourceCodeTable.hpp"
#include <fstream>
using namespace std;

class Pass1 {
public:
    Pass1(string path);
    void mainLoop();
private:
    SourceCodeTable sourceCodeTable;
    int getLengthOf(std::string);
    string path;
    void writeCurrenLineToIntermediateFile(string);
};

#endif /* Pass1_hpp */
