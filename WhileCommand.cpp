//
// Created by alon on 24/12/2019.
//

#include "WhileCommand.h"
#include "ConditionParser.h"

int WhileCommand::execute(vector<string> *param, int index, SymbolTable *symt) {
    map<string, Command*> commandMap = initializeCommandMap();
    Interpreter* interp = symt->getInterpreter();
    Expression* e = interp->interpret((*param)[index]);
    index++;
    int comIndex = index;
    while (e->calculate() != 0) {
        comIndex = index;
        while ((*param)[comIndex] != "}") {
            Command* c = NULL;
            auto it = commandMap.find((*param)[comIndex]);
            if (it != commandMap.end()) {
                c= it->second;
                comIndex += c->execute(param, comIndex+1, symt);
            } else {
                comIndex++;
            }
        }
    }
    return 2;
}



