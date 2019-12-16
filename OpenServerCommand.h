//
// Created by alon on 16/12/2019.
//

#ifndef MILESTONE1__OPENSERVERCOMMAND_H_
#define MILESTONE1__OPENSERVERCOMMAND_H_
#include <string>
#include "Command.h"
#include <vector>

class OpenServerCommand : public Command{
  void getData(int);


 public:
  OpenServerCommand();
  int execute(vector<string> param);
};

#endif //MILESTONE1__OPENSERVERCOMMAND_H_
