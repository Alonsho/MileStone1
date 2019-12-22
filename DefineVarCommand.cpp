//
// Created by dorgamliel on 21/12/2019.
//

#include <iostream>
#include <string.h>
#include "DefineVarCommand.h"

//creates a variable based on current index in vector, and adds it into symbol table.
//Under the assumption only lines which begin with "var" will run here.
int DefineVarCommand::execute(vector<std::__cxx11::string> param, int index, class SymbolTable * symt) {
    map<string, Variable*>* varMap = symt->getVarMap();
    index++;
    string varName = param[index];
    Variable* var;
    Arrow arrow;
    //choosing relevant arrow for Variable.
    if (param[index + 1] == "->") {
        //creating a new variable from txt file.
        arrow = Arrow::Right;
    } else if (param[index + 1] == "<-") {
        arrow = Arrow::Left;
    } else {
        arrow = Arrow ::None;
    }

    //in each line which contains "sim", we create new Variable and put it in both map and array.
    if (param[index+2] == "sim") {
        //fix path.
        string str = param[index+3].substr(0, param[index+3].size()-1);
        str = str.substr(1);

        //check if Variable already exists.
        int ptr = findIdenticalVar(str, *symt);
        //does not exist in simulator array.
        if ( ptr == -1){
            var = new Variable(str ,arrow);
            //exists in simulator array.
        } else {
            var = symt->getSimMap()[ptr];
            var->setDirection(arrow);
        }
        //Iterate through XML file and look for a match.
        for (int j=0; j < 36 ;j++){
            //If there is a match, add variable to map, and array (on index j).
            if (symt->getXMLArr()[j].compare(str) == 0) {
                symt->addToMapAndArr(var, param[index], j);
                break;
            }
        }
    } else {
        //In case a new variable is being equated to a pre-defined variable.
        symt->addToMap(symt->getVarMap()->find(param[index+2])->second, param[index]);
    }
    return 4;

}

//this function checks whether a variable already exists in array, and returns its index if it does, -1 if doesn't.
int DefineVarCommand::findIdenticalVar(string str, SymbolTable symt) {
    int size = symt.getSimMap().size();
    for (int i=0; i < size; i++){
        if (str.compare(symt.getSimMap()[i]->getPath()) == 0) {
            return i;
        }
    }
    return -1;
}