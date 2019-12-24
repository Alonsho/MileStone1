#include "SymbolTable.h"
//
// Created by alon on 16/12/2019.
//

#include "SymbolTable.h"
#include "Command.h"
#include <queue>
std::mutex mutex_lock;

SymbolTable::SymbolTable() {
    initXMLArr();
    initSimArr();
    interp = new Interpreter();
}

map<string, Variable*>* SymbolTable::getVarMap() {
    return &varMap;
}

array<Variable*, 36> SymbolTable::getSimMap() {
    return simArr;
}

//this function updates variable and simulator (according to arrow direction).
string SymbolTable::editVarMap(string key, double value) {
    mutex_lock.lock();
    //create variable value interpretation.
    interp->setVariables((key + "=" + to_string(value)));
    //change value.
    this->varMap.find(key)->second->setValue(value);
    //if arrow points right, update simulator.
    if (this->varMap.find(key)->second->getDirection() == Arrow::Right){
        string st1 = "set ";
        string st2 = this->varMap.find(key)->second->getPath();
        string st3 = st1.append(st2);
        string st4 = to_string(this->varMap.find(key)->second->getValue());
        st3 = st3.append(" ");
        string st5 = st3.append(st4);
        string st6 = st5.append("\r\n");
        this->infoQueue.push(st6);
        mutex_lock.unlock();
        return key;
    }
    mutex_lock.unlock();
    return "";
}

//this function updates variable from simulator, according to arrow direction.
void SymbolTable::editSimArr(int key, double value) {
    mutex_lock.lock();
    //update variable if arrow points left.
    if (this->simArr[key]->getDirection() == Arrow::Left){
        //update new value of variable.
        this->simArr[key]->setValue(value);
        string varName = simArr[key]->getName();
        //interpret new value of variable.
        interp->setVariables((varName + "=" + to_string(value)));
    }
    mutex_lock.unlock();
}

//this function adds a new variable to both map and array.
void SymbolTable::addToMapAndArr(Variable* var, string name, int index) {
    mutex_lock.lock();
    this->varMap.insert({name, var});
    this->simArr[index+1] = var;
    var->setName(name);
    //adding it to interpreter, so that in "execute" command we'll get a double type.
    interp->setVariables((name + "=" + to_string(var->getValue())));
    mutex_lock.unlock();
}

//this function adds a new variable only to a map (if variable is dependant on another variable).
void SymbolTable::addToMap(Variable* var, string st){
    mutex_lock.lock();
    this->varMap.insert({st, var});
    string varName = var->getName();
    interp->setVariables((varName + "=" + to_string(var->getValue())));
    mutex_lock.unlock();
}

//initializing XML array (XML file content).
void SymbolTable::initXMLArr() {
    xmlArr[0] = ("/instrumentation/airspeed-indicator/indicated-speed-kt");
    xmlArr[1] = "/sim/time/warp";
    xmlArr[2] = "/controls/switches/magnetos";
    xmlArr[3] = "/instrumentation/heading-indicator/offset-deg";
    xmlArr[4] = "/instrumentation/altimeter/indicated-altitude-ft";
    xmlArr[5] = "/instrumentation/altimeter/pressure-alt-ft";
    xmlArr[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    xmlArr[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    xmlArr[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    xmlArr[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
    xmlArr[10] = "/instrumentation/encoder/indicated-altitude-ft";
    xmlArr[11] = "/instrumentation/encoder/pressure-alt-ft";
    xmlArr[12] = "/instrumentation/gps/indicated-altitude-ft";
    xmlArr[13] = "/instrumentation/gps/indicated-ground-speed-kt";
    xmlArr[14] = "/instrumentation/gps/indicated-vertical-speed";
    xmlArr[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
    xmlArr[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    xmlArr[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    xmlArr[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
    xmlArr[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    xmlArr[20] = "/controls/flight/aileron";
    xmlArr[21] = "/controls/flight/elevator";
    xmlArr[22] = "/controls/flight/rudder";
    xmlArr[23] = "/controls/flight/flaps";
    xmlArr[24] = "/controls/engines/engine/throttle";
    xmlArr[25] = "/controls/engines/current-engine/throttle";
    xmlArr[26] = "/controls/switches/master-avionics";
    xmlArr[27] = "/controls/switches/starter";
    xmlArr[28] = "/engines/active-engine/auto-start";
    xmlArr[29] = "/controls/flight/speedbrake";
    xmlArr[30] = "/sim/model/c172p/brake-parking";
    xmlArr[31] = "/controls/engines/engine/primer";
    xmlArr[32] = "/controls/engines/current-engine/mixture";
    xmlArr[33] = "/controls/switches/master-bat";
    xmlArr[34] = "/controls/switches/master-alt";
    xmlArr[35] = "/engines/engine/rpm";
}

//get XML array.
string* SymbolTable::getXMLArr(){return this->xmlArr;}

//initializing sim array.
void SymbolTable::initSimArr() {
    int size = simArr.size();
    for (int i=0; i < size; i++) {
        Variable* v = new Variable("", this->getXMLArr()[i], Arrow::None);
        this->simArr[i] = v;
    }
}


Interpreter* SymbolTable::getInterpreter() {
    return interp;
}
