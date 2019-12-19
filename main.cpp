#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>
#include <thread>
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"


void startServer(vector<string> commandLex);
void startClient(vector<string> commandLex);

using namespace std;
int main() {


    vector<string> commandLex;
    commandLex.push_back("OpenServerCommand");
    commandLex.push_back("5403");
    commandLex.push_back("connectControlClient");
    commandLex.push_back("\"127.0.0.1\"");
    commandLex.push_back("5401");
    thread serverThread(startServer, commandLex);

    thread clientThread(startClient, commandLex);

    /*
    OpenServerCommand server;
    string commandName = "OpenServerCommand";
    string s = "5400";
    stv.push_back(s);
    server.execute(stv);
    if (commandName == "OpenServerCommand") {
        thread th1(&OpenServerCommand::getData, server);
    }
     */
    serverThread.join();
    clientThread.join();
    return 0;
}

void startServer(vector<string> commandLex) {
    OpenServerCommand server;
    for (int i = 0; i < commandLex.size(); i++) {
        if (commandLex[i] == "OpenServerCommand") {
            server.execute(commandLex, i+1);
            break;
        }
    }
}

void startClient(vector<string> commandLex) {
    for (int i = 0; i < commandLex.size(); i++) {
        if (commandLex[i] == "connectControlClient") {
            ConnectCommand client;
            client.execute(commandLex, i+1);
            break;
        }
    }
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