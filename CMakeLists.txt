cmake_minimum_required(VERSION 3.15)
project(MileStone1)

set(CMAKE_CXX_STANDARD 14)

add_executable(MileStone1 Command.h)


add_executable(Main main.cpp OpenServerCommand.cpp OpenServerCommand.h SymbolTable.cpp SymbolTable.h Variable.cpp Variable.h ConnectCommand.cpp ConnectCommand.h Lexer.h Lexer.cpp DefineVarCommand.cpp DefineVarCommand.h Arrow.h)

SET(CMAKE_CXX_FLAGS -pthread)