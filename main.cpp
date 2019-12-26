#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>
#include <thread>
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "Lexer.h"
#include "SymbolTable.h"
#include "Interpreter.h"
#include "WhileCommand.h"
<<<<<<< HEAD
#include "IfCommand.h"

void startServer(vector<string>* commandLex, int i, OpenServerCommand* server, SymbolTable* symt);
void startClient(vector<string>* commandLex, int i, ConnectCommand* client, SymbolTable* symt);
map<string, Command*> initializeCommandMap();
=======
>>>>>>> 5653770e076a077ea65eedd670f03583b37ef333
void parse(vector<string> *lexer, map<string, Command*>* commandMap, SymbolTable* symt);

using namespace std;
int main() {


    map<string, Command*> commandMap = ConditionParser::initializeCommandMap();
    SymbolTable symt;
    vector<string> commandLex = lexFile("fly.txt");
    parse(&commandLex, &commandMap, &symt);
    return 0;
}

<<<<<<< HEAD
void startServer(vector<string>* commandLex, int i, OpenServerCommand* server, SymbolTable* symt) {
    server->execute(commandLex, i+1, symt);
}

void startClient(vector<string>* commandLex, int i, ConnectCommand* client, SymbolTable* symt) {
    client->execute(commandLex, i+1, symt);
}


map<string, Command*> initializeCommandMap() {
    map<string, Command*> commandMap;
    auto* server = new OpenServerCommand();
    commandMap["openDataServer"] = server;
    auto* client = new ConnectCommand();
    commandMap["connectControlClient"] = client;
    auto* def = new DefineVarCommand();
    commandMap["var"] = def;
    auto* pr = new PrintCommand();
    commandMap["Print"] = pr;
    auto* sl = new SleepCommand();
    commandMap["Sleep"] = sl;
    AssignCommand* as = new AssignCommand();
    commandMap["="] = as;
    auto* wh = new WhileCommand();
    commandMap["while"] = wh;
    auto* _if = new IfCommand();
    commandMap["if"] = _if;

    // SHOULD ADD WHILE AND IF COMMANDS AND FUNC COMMANDS
    return commandMap;

}

=======
>>>>>>> 5653770e076a077ea65eedd670f03583b37ef333

//parsing each line of text file. MISSING - editing variables (from lex index 116).
void parse(vector<string> *lexer, map<string, Command*>* commandMap, SymbolTable* symt) {
    int index = 0;
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
    symt->setDone();
}
