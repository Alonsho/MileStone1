//
// Created by alon on 16/12/2019.
//

#include "Variable.h"
#include "Arrow.h"


using namespace std;

Variable::Variable(string sym, Arrow dir ) {

    path = sym;
    direction = dir;
}