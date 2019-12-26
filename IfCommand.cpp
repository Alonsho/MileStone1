//
// Created by dorgamliel on 26/12/2019.
//

#include "IfCommand.h"
#include "ConditionParser.h"

int IfCommand::execute(vector<string> *param, int index, SymbolTable *symt) {
    map<string, Command*> commandMap = initializeCommandMap();
    Interpreter* interp = symt->getInterpreter();
    Expression* e = interp->interpret((*param)[index]);
    int comIndex = 0;
    //checking condition of if statement.
    if (e->calculate() != 0) {
        comIndex = index + 1;
        //going through scope.
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
    //if condition is not met, skip scope.
    if (comIndex == 0) {
        comIndex = index + 1;
        while ((*param)[comIndex] != "}") {
            comIndex++;
        }
    }
    return (comIndex-index+1);
}