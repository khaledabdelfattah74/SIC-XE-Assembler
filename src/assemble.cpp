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

    //Pass I
    string path = "test.txt";
    Pass1 pass1(path);
    cout << endl << "An intermediate file was written to the path: " << pass1.outPath << endl;

    if(!pass1.error) {
        cout << "Pass1 assembled successfully" << endl << endl;
        //Pass II
        Pass2 pass2;
        int successful = pass2.excute(pass1.outPath);
        if (!successful) {
            cout << pass2.getErrorMessage();
        }
   } else {
        cout << "Pass1 assembled unsuccessfully" << " : # of errors = " << pass1.getNumOfErrors() << endl;
        cout << pass1.getErrorsReport();
    }
}
