//
// Created by dorgamliel on 26/12/2019.
//

#ifndef MILESTONE1_IFCOMMAND_H
#define MILESTONE1_IFCOMMAND_H

#include "ConditionParser.h"
class IfCommand : public ConditionParser{

public:
    IfCommand() {};
    int execute(vector<string>* param, int index, SymbolTable* symt);
};


#endif //MILESTONE1_IFCOMMAND_H
