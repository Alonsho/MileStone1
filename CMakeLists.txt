cmake_minimum_required(VERSION 3.15)
project(MileStone1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Main main.cpp OpenServerCommand.cpp OpenServerCommand.h SymbolTable.cpp SymbolTable.h Variable.cpp Variable.h ConnectCommand.cpp ConnectCommand.h Lexer.h Lexer.cpp DefineVarCommand.cpp DefineVarCommand.h Arrow.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h AssignCommand.cpp AssignCommand.h Interpreter.cpp Interpreter.h Expression.cpp Expression.h ConditionParser.cpp ConditionParser.h WhileCommand.cpp WhileCommand.h)

SET(CMAKE_CXX_FLAGS -pthread)