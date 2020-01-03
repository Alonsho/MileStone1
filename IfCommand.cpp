//
// Created by dorgamliel on 26/12/2019.
//

#include "IfCommand.h"
#include "ConditionParser.h"


extern map<string, Command*> commandMap;
int IfCommand::execute(vector<string> *param, int index, SymbolTable *symt) {
    Interpreter* interp = symt->getInterpreter();
    Expression* e = interp->interpret((*param)[index]);
    int comIndex = 0;
    //checking condition of if statement.
    if (e->calculate() != 0) {
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
        int numOfParen = 0;
        while ((*param)[comIndex] != "}" || numOfParen > 0) {
            if ((*param)[comIndex] == "{") {
                numOfParen++;
            }
            if ((*param)[comIndex] == "}") {
                numOfParen--;
            }
            comIndex++;
        }
    }
    delete e;
    return (comIndex-index+2);
}