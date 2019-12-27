//
// Created by alon on 24/12/2019.
//

#include "ConditionParser.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "AssignCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"

map<string, Command*> ConditionParser::initializeCommandMap() {
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
    auto* as = new AssignCommand();
    commandMap["="] = as;
    auto* wh = new WhileCommand();
    commandMap["while"] = wh;
    auto* _if = new IfCommand();
    commandMap["if"] = _if;

    // SHOULD ADD WHILE AND IF COMMANDS AND FUNC COMMANDS
    return commandMap;
}

void ConditionParser::cleanMap(map<string, Command*> commandMap) {
    auto it = commandMap.begin();
    while (it != commandMap.end()){
        delete it->second;
        it++;
    }
}