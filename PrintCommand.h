//
// Created by alon on 21/12/2019.
//

#ifndef MILESTONE1__PRINTCOMMAND_H_
#define MILESTONE1__PRINTCOMMAND_H_
#include <string>
#include "Command.h"

class PrintCommand : public Command {


 public:
  PrintCommand() {};
  int execute(vector<string>* param, int index, SymbolTable* symt);
};

#endif //MILESTONE1__PRINTCOMMAND_H_
