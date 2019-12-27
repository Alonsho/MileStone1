//
// Created by alon on 24/12/2019.
//

#ifndef MILESTONE1__CONDITIONPARSER_H_
#define MILESTONE1__CONDITIONPARSER_H_

#include "Command.h"
class ConditionParser : public Command {
 public:
  ConditionParser() {};
  virtual int execute(vector<string>* param, int index, SymbolTable* symt) = 0;
  static map<string, Command*> initializeCommandMap();
  static void cleanMap(map<string, Command*>);
};

#endif //MILESTONE1__CONDITIONPARSER_H_
