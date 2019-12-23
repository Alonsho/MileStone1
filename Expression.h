//
// Created by alon on 22/12/2019.
//

#ifndef MILESTONE1__EXPRESSION_H_
#define MILESTONE1__EXPRESSION_H_

#include <string>
using namespace std;

class Expression {

 public:
  virtual double calculate() = 0;
  virtual ~Expression() {}
};


class Value: public Expression {
 private:
  double val;
 public:
  Value(double);
  double calculate();

};

class UnaryOperator: public Expression {
 protected:
  Expression* e;
 public:
  ~UnaryOperator();
};

class UPlus: public UnaryOperator {
 public:
  UPlus(Expression*);
  double calculate();
};

class UMinus: public UnaryOperator {
 public:
  UMinus(Expression*);
  double calculate();
};

class BinaryOperator: public Expression {
 protected:
  Expression* right;
  Expression* left;
  ~BinaryOperator();
};

class Plus: public BinaryOperator {
 public:
  Plus(Expression*, Expression*);
  double calculate();
};

class Minus: public BinaryOperator {
 public:
  Minus(Expression*, Expression*);
  double calculate();
};

class Mul: public BinaryOperator {
 public:
  Mul(Expression*, Expression*);
  double calculate();
};

class Div: public BinaryOperator {
 public:
  Div(Expression*, Expression*);
  double calculate();
};

class BooleanExpression : public BinaryOperator {

};

class Greater : public BooleanExpression {
 public:
  Greater(Expression*, Expression*);
  double calculate();

};

class GreaterEqual : public BooleanExpression {
 public:
  GreaterEqual(Expression*, Expression*);
  double calculate();

};

class Smaller : public BooleanExpression {
 public:
  Smaller(Expression*, Expression*);
  double calculate();

};

class SmallerEqual : public BooleanExpression {
 public:
  SmallerEqual(Expression*, Expression*);
  double calculate();

};

class Equal : public BooleanExpression {
 public:
  Equal(Expression*, Expression*);
  double calculate();

};

class NotEqual : public BooleanExpression {
 public:
  NotEqual(Expression*, Expression*);
  double calculate();

};

class Var: public Expression {
 private:
  string name;
  double value;
 public:
  Var(string, double);
  double calculate();
  Var& operator ++();
  Var& operator --();
  Var& operator +=(double);
  Var& operator -=(double);
  Var& operator ++(int);
  Var& operator --(int);
};

#endif //MILESTONE1__EXPRESSION_H_
