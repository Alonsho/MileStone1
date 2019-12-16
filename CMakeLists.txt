cmake_minimum_required(VERSION 3.15)
project(MileStone1)

set(CMAKE_CXX_STANDARD 14)

add_executable(MileStone1 client.cpp Command.h)

add_executable(ServerRun server.cpp)

add_executable(Main main.cpp OpenServerCommand.cpp OpenServerCommand.h SymbolTable.cpp SymbolTable.h Variable.cpp Variable.h)

SET(CMAKE_CXX_FLAGS -pthread)