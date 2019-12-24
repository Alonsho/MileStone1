//
// Created by alon on 24/12/2019.
//

#ifndef MILESTONE1__WHILECOMMAND_H_
#define MILESTONE1__WHILECOMMAND_H_

#include "ConditionParser.h"
class WhileCommand : public ConditionParser{

 public:
  WhileCommand() {};
  int execute(vector<string>* param, int index, SymbolTable* symt);
};

#endif //MILESTONE1__WHILECOMMAND_H_
