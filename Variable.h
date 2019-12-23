//
// Created by dorgamliel on 21/12/2019.
//

#ifndef MILESTONE1__VARIABLE_H_
#define MILESTONE1__VARIABLE_H_
#include <string>
#include "Arrow.h"


using namespace std;
class Variable {
private:
    double value = 0;
    string path;
    string name;
    Arrow direction;

public:
    Variable(string st, string sym, Arrow dir)  {
        path = sym; direction = dir; name = st;
    }
    double getValue() {return value; }
    string getPath() { return path; }
    Arrow getDirection() { return direction; }
    void setValue(double v) { this->value = v; }
    void setDirection(Arrow arrow) {this->direction = arrow;}
    string getName() {return name;}
    void setName(string st) {name = st;}
};

#endif //MILESTONE1__VARIABLE_H_