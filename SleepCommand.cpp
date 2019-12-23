//
// Created by alon on 21/12/2019.
//

#include <unistd.h>
#include "SleepCommand.h"

int SleepCommand::execute(vector<string> * param, int index, class SymbolTable * symt) {
    Interpreter* interp = symt->getInterpreter();
    Expression* e = interp->interpret((*param)[index]);
    int secs = e->calculate() / 1000;
    sleep(secs);
    return 2;
}