//
// Created by alon on 19/12/2019.
//

#include "DefineVarCommand.h"


int DefineVarCommand::execute(vector<string>* param, int index, class SymbolTable * symt) {
    map<string, Variable*>* varMap = symt->getMap();
    string varName = (*param)[index];
    index++;
    if ((*param)[index] == "->") {
    }
}