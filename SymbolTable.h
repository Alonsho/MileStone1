//
// Created by dorgamliel on 21/12/2019.
//

#ifndef MILESTONE1__SYMBOLTABLE_H_
#define MILESTONE1__SYMBOLTABLE_H_
#include <map>
#include "Variable.h"
#include <mutex>
#include <vector>
#include "Interpreter.h"
using namespace std;
class SymbolTable {
 private:
  map<string, Variable*> varMap;
  array<Variable*, 36> simArr;
  string xmlArr[36];
  Interpreter* interp;


public:
    SymbolTable();
    map<string, Variable*>* getVarMap();
    array<Variable*, 36> getSimMap();
    void addToMapAndArr(Variable* var, string, int);
    void editSimArr(int, double);
    string editVarMap(string, double);
    void initXMLArr();
    void initSimArr();
    void addToMap(Variable*, string);
    string* getXMLArr();
    Interpreter* getInterpreter();


};

#endif //MILESTONE1__SYMBOLTABLE_H_
