cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled src/main.cpp  src/Entry.cpp src/Entry.hpp src/DisplacementCalculator.cpp src/DisplacementCalculator.h src/AddresingModifier.cpp src/AddresingModifier.h src/IntermediateFileParser.cpp src/IntermediateFileParser.hpp src/LabelProcessor.cpp src/LabelProcessor.h src/Literal.cpp src/Literal.h src/LitTab.cpp src/LitTab.h src/ObjectProgramGenerator.cpp src/ObjectProgramGenerator.h src/OpTable.cpp src/OpTable.hpp src/Pass1.cpp src/Pass1.hpp src/SicParser.cpp src/SicParser.hpp src/SourceCodeTable.cpp src/SourceCodeTable.hpp src/SymTable.cpp src/SymTable.hpp src/Utilities.cpp src/Utilities.h src/Validator.cpp src/Validator.hpp src/assemble.cpp src/Pass2.cpp src/Pass2.h src/ExpressionEvaluator.cpp src/ExpressionEvaluator.hpp)