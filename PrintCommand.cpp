//
// Created by alon on 21/12/2019.
//

#include <iostream>
#include "PrintCommand.h"



int PrintCommand::execute(vector<string>* param, int index, class SymbolTable * symt) {
    string toPrint = (*param)[index].substr(1, (*param)[index].size() - 2);
    cout << toPrint << endl;
    return 2;
}