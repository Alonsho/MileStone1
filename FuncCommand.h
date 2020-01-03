//
// Created by dorgamliel on 01/01/2020.
//

#ifndef MILESTONE1_FUNCCOMMAND_H
#define MILESTONE1_FUNCCOMMAND_H


#include "SymbolTable.h"
#include "ConditionParser.h"

class FuncCommand : public ConditionParser {
    Variable* variable;
    int lines;
public:
    FuncCommand() {};
    int execute(vector<string>* param, int index, SymbolTable* symt);

    //This function checks and returns propriety of function's first line (declaration).
    static bool isAFuncCommand(vector<string>* param, int index) {
        string s1 = (*param)[index+1].substr(0, (*param)[index+1].find(' ')) ;
        string s2 = (*param)[index+2];
        return s1 == "var" && s2 == "{";
    }

    //This function adds a parameter of function to function as its variable (which contains a numeric value).
    void addParamToFunc(SymbolTable* symt, vector<string> *lexer, int index) {
        string s = (*lexer)[index].substr((*lexer)[index].find(' '));
        s.erase(0, 1);
        auto* var = new Variable(s, "", Arrow::None);
        symt->addToMap(var, s);
        variable = var;
    }

    //this function returns the number of lines in scope.
    int countFuncLines(vector<string> *lexer, int index){
        int tempInd = index;
        int bracketCounter = 0;
        //iterates scope and checks if we have reached the relevant closing bracket.
        while ((*lexer)[tempInd] != "}" || bracketCounter != 1) {
            if ((*lexer)[tempInd] == "{") {
                bracketCounter++;
            }
            if ((*lexer)[tempInd] == "}") {
                bracketCounter--;
            }
            tempInd++;
        }
        //updating scope size.
        lines = tempInd - index;
        return lines;
    }
};


#endif //MILESTONE1_FUNCCOMMAND_H
