//
// Created by alon on 16/12/2019.
//

#ifndef MILESTONE1__COMMAND_H_
#define MILESTONE1__COMMAND_H_
# include <vector>
using namespace std;
/**
 * Expression Interface
 */
class Command {

 public:
  virtual int execute(vector<string> param) = 0;
  virtual ~Command() {}
};

#endif //MILESTONE1__COMMAND_H_
