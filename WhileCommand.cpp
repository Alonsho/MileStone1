//
// Created by alon on 24/12/2019.
//

#include "WhileCommand.h"
#include "ConditionParser.h"

//execution of a while command; iterating over commands in scope and executing them.
int WhileCommand::execute(vector<string> *param, int index, SymbolTable *symt) {
    //Initializing a map of Command objects.
    map<string, Command*> commandMap = initializeCommandMap();
    Interpreter* interp = symt->getInterpreter();
    //Interpreting while command expression.
    Expression* e = interp->interpret((*param)[index]);
    int comIndex = 0;
    //Check if condition of while command in text file is met.
    while (e->calculate() != 0) {
        //skipping index of opening bracket.
        comIndex = index + 1;
        //while scope.
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
        e = interp->interpret((*param)[index]);
    }
    //if was not met from the beginning, skip scope.
    if (comIndex == 0) {
        //index inside scope (skipping opening bracket).
        comIndex = index + 1;
        while ((*param)[comIndex] != "}") {
            comIndex++;
        }
    }
    ConditionParser::cleanMap(commandMap);

    //index of closing bracket - index of while condition + 1.
    return (comIndex-index+1);
}



