//
// Created by alon on 22/12/2019.
//

#include "Interpreter.h"
#include <cstring>
#include <regex>
#include <queue>
#include <stack>

using namespace std;


Interpreter::~Interpreter() {
}

// add variables that are to be recognized by the interpreter
void Interpreter::setVariables(string str) {
    char* input = &str[0];
    char* tok = strtok(input, "=");
    char* varName;
    char* varValue;
    // syntax of variable name
    regex name("([A-z]|_)([0-9]|[A-z]|_)*");
    // syntax of value
    regex value("(([-\\+]?)[0-9]+(\\.([0-9]+)))|(([-\\+]?)[0-9]+)");
    // tok will switch between name of the variable and the value
    while (tok != NULL) {
        varName = tok;
        tok = strtok(NULL, ";");
        varValue = tok;
        //if var name is legal, and value is legal.
        if (regex_match(varName, name) && regex_match(varValue, value)) {
            try {
                map<string, double>::iterator it = this->vars.find(varName);
                //if a variable appears again in file, update its new value (to enable calculation in case of expr).
                if (it != this->vars.end()) {
                    it->second = stod(varValue);
                } else {
                    //add new variable to interpreter map.
                    this->vars.insert({varName, stod(varValue)});
                }
            } catch (...) {
                throw ("invalid input");
            }
        } else {
            throw ("invalid input");
        }
        tok = strtok(NULL, "=");
    }
    return;
}


// create an expression out of a string (if it is indeed a mathematical expression) using shunting yard algo.
// "-u" = unary minus and "+u" = unary plus
Expression* Interpreter::interpret(string str) {
    queue<string> operands;
    stack<string> operators;
    size_t prev = 0;
    size_t pos = 1;
    string token;
    // remove spaces
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    // checks if first character is an operator
    token = str.substr(0, 1);
    if (stringIsOperator(token)) {
        if (token == "-" && !isdigit(str.substr(1, 1)[0])) {
            insertOperator("-u", &operands, &operators);
        } else if (token == "-" && isdigit(str.substr(1, 1)[0])) {
            pos = str.find_first_of("/*+-()<>=!", 1);
            token = str.substr(0, pos);
            operands.push(token);
        } else if (token == "+" && !isdigit(str.substr(1, 1)[0])) {
            insertOperator("+u", &operands, &operators);
        } else if (token == "+" && isdigit(str.substr(1, 1)[0])) {
            pos = str.find_first_of("/*+-()<>=!", 1);
            token = str.substr(0, pos);
            operands.push(token);
        } else {
            insertOperator(token, &operands, &operators);
        }
        prev = pos;
    } else if (token == "(") {
        operators.push(token);
        prev++;
    // first character is part of a number, add the number as an operand
    } else {
        pos = str.find_first_of("/*+-()<>=!", 0);
        token = str.substr(prev, pos - prev);
        prev = pos;
        operands.push(token);
    }
    // find the location of the next operator
    pos = str.find_first_of("/*+()-<>=!", prev);
    // run on all the string
    while (pos != string::npos) {
        // advance prev to next part
        if (pos == prev) {
            token = str.substr(prev, 2);
            if (token == "<=" || token == ">=" || token == "==" || token == "!=") {
                prev += 2;
            } else {
                token = token.substr(0, 1);
                prev++;
            }
        } else {
            token = str.substr(prev, pos - prev);
            prev = pos;
        }
        // check if current token is operator and insert the correct operator to operator stack
        if (stringIsOperator(token)) {
            if (token[0] == '-' && str.substr(prev, 1) == "(" && str.substr(prev - 2, 1) == "(") {
                insertOperator("-u", &operands, &operators);
            } else if (token[0] == '-' && str.substr(prev - 2, 1) == "(" && isdigit(str.substr(prev, 1)[0])) {
                pos = str.find_first_of("/*+-()<>=!", prev);
                token = str.substr(prev - 1, pos - prev + 1);
                operands.push(token);
                prev = pos;
            } else if (token[0] == '+' && str.substr(prev, 1) == "(" && str.substr(prev - 2, 1) == "(") {
                insertOperator("+u", &operands, &operators);
            } else if (token[0] == '+' && str.substr(prev - 2, 1) == "(" &&  isdigit(str.substr(prev, 1)[0])) {
                pos = str.find_first_of("/*+-()<>=!", prev);
                token = str.substr(prev - 1, pos - prev + 1);
                operands.push(token);
                prev = pos;
            } else {
                insertOperator(token, &operands, &operators);
            }
            // token is an operand
        }  else {
            operands.push(token);
        }
        // advance pos
        pos = str.find_first_of("/*+()-<>=!", prev);
        if (pos == string::npos && prev != str.length()) {
            pos = str.length();
        }
    }
    // moves operators to operand queue
    emptyOperatorStack(&operands, &operators);
    return convertToExpression(&operands);

}

// checks if a given string is an operator
bool Interpreter::stringIsOperator(string token) {
    if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '(' || token[0] == ')'
        || token[0] == '<' || token[0] == '>' || token == "<=" || token == ">=" || token == "==" || token == "!=") {
        return true;
    } else {
        return false;
    }
}


// inserts a operator to the stack while moving those who have higher precedence to operands queue
void Interpreter::insertOperator(string token, queue<string>* operands, stack<string>* operators) {
    if (!operators->empty() && (token == "<" || token == ">" || token == "<=" || token == ">="||
        token == "==" || token == "!=")) {
        while (!operators->empty() && (operators->top() == "/" || operators->top() == "*" ||
            operators->top() == "+" || operators->top() == "-" || operators->top() == "-u" ||
            operators->top() == "+u" || operators->top() == "<" || operators->top() == ">" ||
            operators->top() == "<=" || operators->top() == ">=" || operators->top() == "==" || operators->top() == "!=")) {
            operands->push(operators->top());
            operators->pop();
        }
    }
    if (!operators->empty() && (token == "*" || token == "/")) {
        while (!operators->empty() && (operators->top() == "/" || operators->top() == "*" ||
            operators->top() == "-u" || operators->top() == "+u")) {
            operands->push(operators->top());
            operators->pop();
        }
        operators->push(token);
    }  else if (token == "+" || token == "-") {
        while (!operators->empty() && (operators->top() == "/" || operators->top() == "*" ||
            operators->top() == "+" || operators->top() == "-" || operators->top() == "-u" || operators->top() == "+u")) {
            operands->push(operators->top());
            operators->pop();
        }
        operators->push(token);
    } else if (token == "+u" || token == "-u") {
        while (!operators->empty() && (operators->top() == "-u" || operators->top() == "+u")) {
            operands->push(operators->top());
            operators->pop();
        }
        operators->push(token);
    } else if (token == ")") {
        if (operators->empty()) {
            throw "bad input(wrong paranthes)";
        }
        while (operators->top() != "(") {
            if (operators->size() == 1) {
                throw "bad input(wrong paranthes)";
            }
            try {
                operands->push(operators->top());
                operators->pop();
            } catch (...) {
                throw "bad input(wrong paranthes)";
            }
        }
        operators->pop();
    }  else {
        operators->push(token);
    }
}


// moves all the operator stack into the operand queue
void Interpreter::emptyOperatorStack(queue<string>* operands, stack<string>* operators) {
    while (!operators->empty()) {
        operands->push(operators->top());
        operators->pop();
    }
}


// creates and Expression out of the operand queue (which now includes also the operators)
Expression* Interpreter::convertToExpression(queue<string>* operands) {
    stack<Expression*> expressions;
    Expression* e;
    // pops out one argument at a time, creates an expression from it (and from operands)
    // and pushes into Expression stack
    while (!operands->empty()) {
        if (operands->front() == "*") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new Mul(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (mult)";
            }
        } else if (operands->front() == "/") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new Div(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (div)";
            }
        } else if (operands->front() == "+") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new Plus(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (plus)";
            }
        } else if (operands->front() == "-") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new Minus(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (minus)";
            }
        } else if (operands->front() == "-u") {
            if (expressions.size() < 1) {
                throw "bad input (too many operators)";
            }
            try {
                e = new UMinus(expressions.top());
                expressions.pop();
                expressions.push(e);
            } catch (...) {
                throw "bad input (UMinus)";
            }
        } else if (operands->front() == "+u") {
            if (expressions.size() < 1) {
                throw "bad input (too many operators)";
            }
            try {
                e = new UPlus(expressions.top());
                expressions.pop();
                expressions.push(e);
            } catch (...) {
                throw "bad input (Uplus)";
            }
        } else if (operands->front() == "<") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new Smaller(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (smaller)";
            }
        } else if (operands->front() == ">") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new Greater(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (greater)";
            }
        } else if (operands->front() == "<=") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new SmallerEqual(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (smaller or equal)";
            }
        } else if (operands->front() == ">=") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new GreaterEqual(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (greater or equal)";
            }
        } else if (operands->front() == "==") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new Equal(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (equal)";
            }
        } else if (operands->front() == "!=") {
            if (expressions.size() < 2) {
                throw "bad input (too many operators)";
            }
            try {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                e = new NotEqual(left, right);
                expressions.push(e);
            } catch (...) {
                throw "bad input (not equal)";
            }
        } else if (vars.find(operands->front()) != vars.end()) {
            try {
                e = new Var(operands->front(), vars.find(operands->front())->second);
                expressions.push(e);
            } catch (...) {
                throw "bad input (bad variable)";
            }
        } else {
            try {
                e = new Value(stod(operands->front()));
                expressions.push(e);
            } catch (...) {
                if (operands->front() == "(") {
                    throw "bad input (bad parantheses)";
                }
                throw "bad input (bad variable)";
            }
        }
        operands->pop();
    }
    if (expressions.size() != 1) {
        throw "bad input (too many operands)";
    }
    return expressions.top();
}