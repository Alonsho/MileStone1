#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>
#include "Command.h"
#include "Lexer.h"
#include "SymbolTable.h"
#include "Interpreter.h"
#include "ConditionParser.h"
#include "FuncCommand.h"

void parse(vector<string> *lexer, SymbolTable* symt);
void closeSockets();


map<string, Command*> commandMap;
extern bool clientSocketRunning;
extern bool serverSocketRunning;
using namespace std;
int main(int , char *argv[]) {
    if (argv[1] == nullptr) {
        cerr<<"No file name entered."<<endl;
        exit(1);
    }
    commandMap = ConditionParser::initializeCommandMap();
    SymbolTable symt;
    vector<string> commandLex = lexFile(argv[1]);
    parse(&commandLex, &symt);
    ConditionParser::cleanMap(commandMap);
    closeSockets();
    return 0;
}

//parsing each line of text file. MISSING - editing variables (from lex index 116).
void parse(vector<string> *lexer, SymbolTable* symt) {
    vector<string> funcVec;
    unsigned int index = 0;
    while (index < lexer->size()) {
        Command* c = NULL;
        auto it = commandMap.find((*lexer)[index]);
        if (it != commandMap.end()) {
            c= it->second;
            index += c->execute(lexer, index+1, symt);
        } else if (FuncCommand::isAFuncCommand(lexer,index)){
            auto* func = new FuncCommand();
            func->addParamToFunc(symt, lexer, index + 1);
            //add new function name to function names vector.
            funcVec.push_back((*lexer)[index]);
            //insert detected function into commands map.
            commandMap.insert({(*lexer)[index].substr(0, (*lexer)[index].find('{')), func});
            //skip function scope after declaration.
            index += func->countFuncLines(lexer, index);
        } else {
            index++;
        }
    }
    //when parsing stage ends, ConnectCommand and OpenServerCommand disconnect (detection by this boolean).
    symt->setDone();
    //remove all deleted functions fom commands map.
    while (!funcVec.empty()){
        commandMap.erase(funcVec.back());
        funcVec.pop_back();
    }
}


void closeSockets() {
    while (clientSocketRunning || serverSocketRunning) {
        sleep(1);
    }
}