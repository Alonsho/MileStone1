//
// Created by dorgamliel on 01/01/2020.
//

#include "FuncCommand.h"


extern map<string, Command*> commandMap;
int FuncCommand::execute(vector<string> *param, int index, SymbolTable *symt) {
    Interpreter* interp = symt->getInterpreter();
    //Interpreting while command expression.
    Expression* e = interp->interpret((*param)[index]);
    this->variable->setValue(e->calculate());
    symt->editVarMap(this->variable->getName(), this->variable->getValue());
    if (lines < index) {
        index -= lines;
    }
    int comIndex = 0;
    comIndex = index + 2;
    //going through scope.
    int numOfParen = 0;
    while ((*param)[comIndex] != "}" || numOfParen > 0) {
        if ((*param)[comIndex] == "{") {
            numOfParen++;
        }
        if ((*param)[comIndex] == "}") {
            numOfParen--;
        }
        Command *c = NULL;
        auto it = commandMap.find((*param)[comIndex]);
        if (it != commandMap.end()) {
            c = it->second;
            comIndex += c->execute(param, comIndex + 1, symt);
        } else {
            comIndex++;
        }
    }
    delete e;
    return 2;
}

