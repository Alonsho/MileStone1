//
// Created by alon on 22/12/2019.
//

#include <iostream>
#include "AssignCommand.h"


int AssignCommand::execute(vector<string> * param, int index, class SymbolTable * symt) {
    try {
        Variable *var = symt->getVarMap()->find((*param)[index - 1])->second;
    } catch (exception e){
        cerr << "variable not found" << endl;
    }

}