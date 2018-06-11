cmake_minimum_required(VERSION 3.10)
project(SIC_XE_Assembler)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(SIC_XE_Assembler
        src/AddresingModifier.cpp
        src/AddresingModifier.h
        src/DisplacementCalculator.cpp
        src/DisplacementCalculator.h
        src/Entry.cpp
        src/Entry.hpp
        src/IntermediateFileParser.cpp
        src/IntermediateFileParser.hpp
        src/LabelProcessor.cpp
        src/LabelProcessor.h
        src/Literal.cpp
        src/Literal.h
        src/LitTab.cpp
        src/LitTab.h
        src/main.cpp
        src/ObjectProgramGenerator.cpp
        src/ObjectProgramGenerator.h
        src/OpTable.cpp
        src/OpTable.hpp
        src/Pass1.cpp
        src/Pass1.hpp
        src/Pass2.cpp
        src/SicParser.cpp
        src/SicParser.hpp
        src/SourceCodeTable.cpp
        src/SourceCodeTable.hpp
        src/SymTable.cpp
        src/SymTable.hpp
        src/Utilities.cpp
        src/Utilities.h
        src/Validator.cpp
        src/Validator.hpp)
