//
// Created by alon on 21/12/2019.
//

#include <unistd.h>
#include "SleepCommand.h"


int SleepCommand::execute(vector<string> * param, int index, class SymbolTable * symt) {
    int secs = stoi((*param)[index]);
    sleep(secs);
    return 2;
}