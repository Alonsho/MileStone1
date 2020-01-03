//
// Created by dorgamliel on 01/01/2020.
//

#include "FuncCommand.h"


extern map<string, Command*> commandMap;

//execution of a function command; iterating over commands in scope and executing them.
int FuncCommand::execute(vector<string> *param, int index, SymbolTable *symt) {
    Interpreter* interp = symt->getInterpreter();
    //Interpreting function command expression.
    Expression* e = interp->interpret((*param)[index]);
    //updates function parameter.
    this->variable->setValue(e->calculate());
    //update variable numeric value in symbol table.
    symt->editVarMap(this->variable->getName(), this->variable->getValue());
    if (lines < index) {
        index -= lines;
    }
    //pointing scope beginning.
    index += 2;
    int parentheses = 0;
    //iterating scope.
    while ((*param)[index] != "}" || parentheses > 0) {
        if ((*param)[index] == "{") {
            parentheses++;
        }
        if ((*param)[index] == "}") {
            parentheses--;
        }
        Command *c = NULL;
        auto it = commandMap.find((*param)[index]);
        //if indexed string is a command, execute it.
        if (it != commandMap.end()) {
            c = it->second;
            index += c->execute(param, index + 1, symt);
        } else {
            index++;
        }
    }
    delete e;
    return 2;
}

