//
// Created by alon on 22/12/2019.
//

#ifndef MILESTONE1__ASSIGNCOMMAND_H_
#define MILESTONE1__ASSIGNCOMMAND_H_
#include "Command.h"

class AssignCommand : public Command {

 public:
  AssignCommand() {};
  int execute(vector<string>* param, int index, SymbolTable* symt);

};

#endif //MILESTONE1__ASSIGNCOMMAND_H_
