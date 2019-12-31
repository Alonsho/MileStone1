#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>
#include "Command.h"
#include "Lexer.h"
#include "SymbolTable.h"
#include "Interpreter.h"
#include "WhileCommand.h"
#include "ConditionParser.h"


void parse(vector<string> *lexer, map<string, Command*>* commandMap, SymbolTable* symt);

using namespace std;
int main() {

    map<string, Command*> commandMap = ConditionParser::initializeCommandMap();
    SymbolTable symt;
    vector<string> commandLex = lexFile("fly.txt");
    parse(&commandLex, &commandMap, &symt);
    ConditionParser::cleanMap(commandMap);
    return 0;
}

//parsing each line of text file. MISSING - editing variables (from lex index 116).
void parse(vector<string> *lexer, map<string, Command*>* commandMap, SymbolTable* symt) {
    unsigned int index = 0;
    while (index < lexer->size()) {
        Command* c = NULL;
        auto it = commandMap->find((*lexer)[index]);
        if (it != commandMap->end()) {
            c= it->second;
            index += c->execute(lexer, index+1, symt);
        } else {
            index++;
        }
    }
    //when parsing stage ends, ConnectCommand and OpenServerCommand disconnect (detection by this boolean).
    symt->setDone();
}
