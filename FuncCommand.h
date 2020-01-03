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
    int getLine(){ return lines; };
    int execute(vector<string>* param, int index, SymbolTable* symt);

    //This function checks and returns propriety of function's first line (declaration).
    static bool isAFuncCommand(vector<string>* param, int index) {
        string s1 = (*param)[index+1].substr(0, (*param)[index+1].find(' ')) ;
        string s2 = (*param)[index+2];
        return s1 == "var" && s2 == "{";
    }

    void addParamToFunc(SymbolTable* symt, vector<string> *lexer, int index) {
        string s = (*lexer)[index].substr((*lexer)[index].find(' '));
        s.erase(0, 1);
        auto* var = new Variable(s, "", Arrow::None);
        symt->addToMap(var, s);
        variable = var;
    }

    //this function returns number of lines in scope.
    int countFuncLines(vector<string> *lexer, int index){
        int tempInd = index;
        int bracketCounter = 0;
        while ((*lexer)[tempInd] != "}" || bracketCounter != 1) {
            if ((*lexer)[tempInd] == "{") {
                bracketCounter++;
            }
            if ((*lexer)[tempInd] == "}") {
                bracketCounter--;
            }
            tempInd++;
        }
        lines = tempInd - index;
        return lines;
    }
};


#endif //MILESTONE1_FUNCCOMMAND_H
