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


void startServer(vector<string>* commandLex, int i, OpenServerCommand* server, SymbolTable* symt);
void startClient(vector<string>* commandLex, int i, ConnectCommand* client, SymbolTable* symt);
map<string, Command*>* initializeCommandMap();

using namespace std;
int main() {


    map<string, Command*>* commandMap = initializeCommandMap();
    SymbolTable symt;
    vector<string> commandLex = lexFile("fly_with_func.txt");
    Command* c = new PrintCommand();
    c->execute(&commandLex, 1, &symt);

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

    serverThread.join();
    clientThread.join();
    return 0;
}

void startServer(vector<string>* commandLex, int i, OpenServerCommand* server, SymbolTable* symt) {
    server->execute(commandLex, i+1, symt);
}

void startClient(vector<string>* commandLex, int i, ConnectCommand* client, SymbolTable* symt) {
    client->execute(commandLex, i+1, symt);
}


map<string, Command*>* initializeCommandMap() {
    map<string, Command*> commandMap;
    OpenServerCommand server;
    commandMap["openDataServer"] = &server;
    ConnectCommand client;
    commandMap["connectControlClient"] = &client;
    DefineVarCommand def;
    commandMap["var"] = &def;
    PrintCommand pr;
    commandMap["Print"] = &pr;
    SleepCommand sl;
    commandMap["Sleep"] = &sl;

    // SHOULD ADD WHILE AND IF COMMANDS AND FUNC COMMANDS
    return &commandMap;

}


/*
void parse(vector<string> *lexer) {
    int index = 0;
    while (index < lexer->size()) {
        Command c = commandMap.get(lexer[index]);
        if (c != NULL) {
            index += c.execute(&lexer[index + 1]);
        } else {
            index++;
        }
    }
}
*/