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
    while (e->calculate() != 0) {
        while ((*param)[index] != "}") {
            Command* c = NULL;
            auto it = commandMap.find((*param)[index]);
            if (it != commandMap.end()) {
                c= it->second;
                index += c->execute(param, index+1, symt);
            } else {
                index++;
            }
        }
    }
    return 2;
}



