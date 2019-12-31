//
// Created by alon on 21/12/2019.
//

#include "SleepCommand.h"
#include <thread>


// puts the thread to sleep for the given time
int SleepCommand::execute(vector<string> * param, int index, class SymbolTable * symt) {
    Interpreter* interp = symt->getInterpreter();
    Expression* e = interp->interpret((*param)[index]);
    int time = e->calculate();
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    delete e;
    return 2;
}