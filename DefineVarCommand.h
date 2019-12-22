//
// Created by alon on 19/12/2019.
//

#ifndef MILESTONE1__DEFINEVARCOMMAND_H_
#define MILESTONE1__DEFINEVARCOMMAND_H_
#include <string>
#include "Command.h"

class DefineVarCommand: public Command {

 public:
  DefineVarCommand() {};
  int execute(vector<string> param, int index, SymbolTable* symt);
  int findIdenticalVar(string, SymbolTable);
};

#endif //MILESTONE1__DEFINEVARCOMMAND_H_
