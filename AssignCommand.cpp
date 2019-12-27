//
// Created by alon on 22/12/2019.
//

#include <iostream>
#include "AssignCommand.h"

//this function assigns a value to a variable.
int AssignCommand::execute(vector<string> * param, int index, class SymbolTable * symt) {
    Interpreter* interp = symt->getInterpreter();
    Expression* e = interp->interpret((*param)[index]);
    double newVal = e->calculate();
    //trying to find variable before assignment execution.
    try {
        Variable *var = symt->getVarMap()->find((*param)[index - 2])->second;
        //edit variable value to new value.
        symt->editVarMap((*param)[index - 2], newVal);
    } catch (exception e){
        cerr << "variable not found" << endl;
    }
    delete e;
    return 2;
}