//
// Created by alon on 16/12/2019.
//

#include "SymbolTable.h"

map<string, Variable*>* SymbolTable::getMap() {
    return &varMap;
}
