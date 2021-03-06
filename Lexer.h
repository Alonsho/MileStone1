
//
// Created by dorgamliel on 19/12/2019.
//

#ifndef MileStone1_VARIABLE_H
#define MileStone1_VARIABLE_H

#include <vector>
#include <string>
using namespace std;

vector<string> splitLine(string st);

void printVector(vector<string>);

string separateAfterEqual(string);

vector<string> split(string, string);

bool arrowIsNext(string, int);

string arrowDirection(string, int);

string separateAfterArrow(string);

vector<string> conditionCheck(string);

vector<string> noSpaceSign(string, string, int);

vector<string> lexFile(string);
string removeIdentations(string);

#endif //MileStone1_LEXER_H
