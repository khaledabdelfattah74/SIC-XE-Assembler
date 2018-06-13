//
// Created by sajed on 11/06/18.
//

#ifndef UNTITLED_PASS2_H
#define UNTITLED_PASS2_H

#include <iostream>
#include "IntermediateFileParser.hpp"
#include "LabelProcessor.h"
#include "AddresingModifier.h"
#include "DisplacementCalculator.h"
#include "OpTable.hpp"
#include "Utilities.h"
#include "ObjectProgramGenerator.h"
#include "ControlSection.hpp"

class Pass2 {
    public:
        Pass2();
        virtual ~Pass2();
        int excute(string, string);
        string getErrorMessage();
    private:
        string errorMessage;
        void debugEntriesVectors(vector<IntermediateFileParser::entry> vectorToDebug);
        void debugLabelAddresses(unordered_map<string,string> addresses);
        void debugAddressMode(vector<IntermediateFileParser::entry> vectorToDebug);
        void debugDisplacement(vector<IntermediateFileParser::entry> vectorToDebug);
        void debugUtilities();
        vector<ControlSection> get_sections(vector<IntermediateFileParser::entry>);
};


#endif //UNTITLED_PASS2_H
