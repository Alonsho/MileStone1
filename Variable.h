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
    Arrow direction;

public:
    Variable(string sym , Arrow dir)  {
        path = sym; direction = dir;
    }
    double getValue() {return value; }
    string getPath() { return path; }
    Arrow getDirection() { return direction; }
    Arrow setValue(double v) { this->value = v; }
    Arrow setDirection(Arrow arrow) {this->direction = arrow;}
};

#endif //MILESTONE1__VARIABLE_H_