//
// Created by dorgamliel on 01/01/2020.
//

#include "FuncCommand.h"
int FuncCommand::execute(vector<string> *param, int index, SymbolTable *symt, map<string, Command*> commandMap1) {
    map<string, Command*> commandMap = initializeCommandMap();
    commandMap.insert(commandMap1.begin(), commandMap1.end());
    Interpreter* interp = symt->getInterpreter();
    //Interpreting while command expression.
    Expression* e = interp->interpret((*param)[index]);
    this->variable->setValue(e->calculate());
    symt->editVarMap(this->variable->getName(), this->variable->getValue());
    if (lines < index) {
        index -= lines;
    }
    int comIndex = 0;
    comIndex = index + 1;
    //going through scope.
    while ((*param)[comIndex] != "}") {
        Command *c = NULL;
        auto it = commandMap.find((*param)[comIndex]);
        if (it != commandMap.end()) {
            c = it->second;
            comIndex += c->execute(param, comIndex + 1, symt, commandMap);
        } else {
            comIndex++;
        }
    }
    delete e;
    return 2;
}

