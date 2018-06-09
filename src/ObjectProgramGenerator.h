//
// Created by ayman on 06/06/18.
//

#ifndef SIC_XE_ASSEMBLER_OBJECTCODEGENERATOR_H
#define SIC_XE_ASSEMBLER_OBJECTCODEGENERATOR_H


#include "IntermediateFileParser.hpp"

class ObjectProgramGenerator {
public:
    void generate_program_code(vector<IntermediateFileParser::entry>);
};


#endif //SIC_XE_ASSEMBLER_OBJECTCODEGENERATOR_H
