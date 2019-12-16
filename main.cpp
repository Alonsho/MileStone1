#include <iostream>
#include <list>
#include <vector>
#include "Command.h"
#include "OpenServerCommand.h"

using namespace std;
int main() {

    OpenServerCommand server;
    vector<string> stv;
    string s = "5400";
    stv.push_back(s);
    server.execute(stv);
    cout<<"back to main"<<std::endl;
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