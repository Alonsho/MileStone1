//
// Created by alon on 21/12/2019.
//

#include <iostream>
#include "PrintCommand.h"

int PrintCommand::execute(vector<string>* param, int index, class SymbolTable * symt) {
    Interpreter* interp = symt->getInterpreter();
    if ((*param)[index][0] == '"') {
        string toPrint = (*param)[index].substr(1, (*param)[index].size() - 2);
        cout << toPrint << endl;
    } else {
        Expression* e = interp->interpret((*param)[index]);
        cout << e->calculate() << endl;
    }
    return 2;
}