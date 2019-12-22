//
// Created by alon on 21/12/2019.
//

#ifndef MILESTONE1__SLEEPCOMMAND_H_
#define MILESTONE1__SLEEPCOMMAND_H_
#include "Command.h"

class SleepCommand : public Command {


 public:
  SleepCommand() {};
  int execute(vector<string>* param, int index, SymbolTable* symt);

};

#endif //MILESTONE1__SLEEPCOMMAND_H_
