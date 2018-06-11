//
// Created by sajed on 11/06/18.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Pass1.hpp"
#include "Pass2.h"


using namespace std;


int main(int argc, const char * argv[]) {

    if (argc < 2) {
        // Tell the user how to run the program
        cout << "Please, Send parameters correctly (Assembly file's path)" << endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
    string path = argv[1];

    string objectCodePath = "";
    objectCodePath.append(path, 0, path.length() - 4);
    objectCodePath.append("ObjectCode.txt");
    remove(objectCodePath.c_str());
    //Pass I
    Pass1 pass1(path);
    cout << endl << "An intermediate file was written to the path: " << pass1.outPath << endl;

    if(!pass1.error) {
        cout << "Pass1 assembled successfully" << endl << endl;
        //Pass II
        Pass2 pass2;
        int successful = pass2.excute(pass1.outPath, objectCodePath);
        if (!successful) {
            cout << pass2.getErrorMessage();
        }
   } else {
        cout << "Pass1 assembled unsuccessfully" << " : # of errors = " << pass1.getNumOfErrors() << endl;
        cout << pass1.getErrorsReport();
    }
}
