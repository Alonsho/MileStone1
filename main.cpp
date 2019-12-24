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
#include "PrintCommand.h"
#include "DefineVarCommand.h"
#include "SleepCommand.h"
#include "Interpreter.h"




void startServer(vector<string>* commandLex, int i, OpenServerCommand* server, SymbolTable* symt);
void startClient(vector<string>* commandLex, int i, ConnectCommand* client, SymbolTable* symt);
map<string, Command*> initializeCommandMap();
void parse(vector<string> *lexer, map<string, Command*>* commandMap, SymbolTable* symt);

using namespace std;
int main() {


    map<string, Command*> commandMap = initializeCommandMap();
    SymbolTable symt;
    vector<string> commandLex = lexFile("fly_with_func.txt");

    OpenServerCommand server;
    int i = 0;
    for (i = 0; i < commandLex.size(); i++) {
        if (commandLex[i] == "openDataServer") {
            break;
        }
    }


    thread serverThread(startServer, &commandLex, i, &server, &symt);
    while (!server.isConnected()) {
        cout << "waiting for connection FROM simulator" << endl;
        sleep(1);
    }

    ConnectCommand client;
    for (i = 0; i < commandLex.size(); i++) {
        if (commandLex[i] == "connectControlClient") {
            break;
        }
    }

    thread clientThread(startClient, &commandLex, i, &client, &symt);
    while (!client.isConnected()) {
        cout << "Trying to establish connection TO simulator" << endl;
        sleep(1);
    }
    //wait for simulator to start (wait until connection is established) DO NOT USE IF USING DANIELAS PYTHON CODE
    //sleep(45);

    parse(&commandLex, &commandMap, &symt);
    serverThread.join();
    clientThread.join();
    delete &symt;
    return 0;
}

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
    auto* sl = new SleepCommand;
    commandMap["Sleep"] = sl;

    // SHOULD ADD WHILE AND IF COMMANDS AND FUNC COMMANDS
    return commandMap;

}



void parse(vector<string> *lexer, map<string, Command*>* commandMap, SymbolTable* symt) {
    int index = 0;
    while (index < lexer->size()) {
        if ((*lexer)[index] == "openDataServer") {
            index += 2;
            continue;
        }
        if ((*lexer)[index] == "connectControlClient") {
            index += 3;
            continue;
        }
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
