//
// Created by alon on 22/12/2019.
//

#ifndef MILESTONE1__INTERPRETER_H_
#define MILESTONE1__INTERPRETER_H_
#include "Expression.h"
#include <map>
#include <queue>
#include <stack>

using namespace std;
class Interpreter {
 private:
  map <string, double> vars;
 public:
  ~Interpreter();
  Expression* interpret(string);
  void setVariables(string);
  bool stringIsOperator(string);
  void insertOperator(string, queue<string>*, stack<string>*);
  void emptyOperatorStack(queue<string>*, stack<string>*);
  Expression* convertToExpression(queue<string>*);

};

#endif //MILESTONE1__INTERPRETER_H_
