//
// Created by alon on 22/12/2019.
//

#include <iostream>
#include <map>
#include "Expression.h"

using namespace std;

Value::Value(double x) {
    this->val = x;
}

double Value::calculate() {
    return this->val;
}

UnaryOperator::~UnaryOperator() {
    delete this->e;
}

UPlus::UPlus(Expression * exp) {
    this->e = exp;
}

double UPlus::calculate() {
    return this->e->calculate();
}

UMinus::UMinus(Expression * exp) {
    this->e = exp;
}

double UMinus::calculate() {
    return (-this->e->calculate());
}

BinaryOperator::~BinaryOperator() {
    delete this->right;
    delete this->left;
}

Plus::Plus(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double Plus::calculate() {
    return (left->calculate() + right->calculate());
}

Minus::Minus(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double Minus::calculate() {
    return (left->calculate() - right->calculate());
}

Mul::Mul(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double Mul::calculate() {
    return (left->calculate() * right->calculate());
}

Div::Div(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double Div::calculate() {
    if (right->calculate() == 0) {
        throw "bad input (division by 0)";
    }
    return (left->calculate() / right->calculate());
}


Greater::Greater(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double Greater::calculate() {
    if (left->calculate() > right->calculate()) {
        return true;
    } else {
        return false;
    }
}


GreaterEqual::GreaterEqual(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double GreaterEqual::calculate() {
    if (left->calculate() >= right->calculate()) {
        return true;
    } else {
        return false;
    }
}


Smaller::Smaller(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double Smaller::calculate() {
    if (left->calculate() < right->calculate()) {
        return true;
    } else {
        return false;
    }
}


SmallerEqual::SmallerEqual(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double SmallerEqual::calculate() {
    if (left->calculate() <= right->calculate()) {
        return true;
    } else {
        return false;
    }
}


Equal::Equal(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double Equal::calculate() {
    if (left->calculate() == right->calculate()) {
        return true;
    } else {
        return false;
    }
}


NotEqual::NotEqual(Expression * e1, Expression * e2) {
    this->left = e1;
    this->right = e2;
}

double NotEqual::calculate() {
    if (left->calculate() != right->calculate()) {
        return true;
    } else {
        return false;
    }
}





Var::Var(string st, double x) {
    this->name = st;
    this->value = x;
}
double Var::calculate() {
    return this->value;
}


Var& Var::operator ++() {
    this->value++;
    return *this;
}

Var& Var::operator --() {
    this->value--;
    return *this;
}

Var& Var::operator +=(double x) {
    this->value += x;
    return *this;
}

Var& Var::operator -=(double x) {
    this->value -= x;
    return *this;
}

Var& Var::operator ++(int) {
    this->value++;
    return *this;
}

Var& Var::operator --(int) {
    this->value--;
    return *this;
}
