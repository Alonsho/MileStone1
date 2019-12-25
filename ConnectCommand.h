//
// Created by alon on 17/12/2019.
//

#ifndef MILESTONE1__CONNECTCOMMAND_H_
#define MILESTONE1__CONNECTCOMMAND_H_
#include <string>
#include "Command.h"
#include <vector>

class ConnectCommand: public Command {

 public:
  ConnectCommand() {
  }
  int execute(vector<string>* param, int index, SymbolTable* symt);
  void sendData(SymbolTable *symt, int client_socket);
};

#endif //MILESTONE1__CONNECTCOMMAND_H_
