//
// Created by alon on 16/12/2019.
//

#ifndef MILESTONE1__VARIABLE_H_
#define MILESTONE1__VARIABLE_H_
#include <string>

using namespace std;
class Variable {
 private:
  double value;
  string path;
  bool RightArrow;

 public:
  Variable(string, string);
  double getValue();
  string getPath();
  bool isRightArrow();


};

#endif //MILESTONE1__VARIABLE_H_
