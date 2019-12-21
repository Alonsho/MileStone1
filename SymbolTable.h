//
// Created by alon on 16/12/2019.
//

#ifndef MILESTONE1__SYMBOLTABLE_H_
#define MILESTONE1__SYMBOLTABLE_H_
#include <map>
#include "Variable.h"

using namespace std;
class SymbolTable {
 private:
  map<string, Variable*> varMap;


 public:
  map<string, Variable*>* getMap();

};

#endif //MILESTONE1__SYMBOLTABLE_H_
