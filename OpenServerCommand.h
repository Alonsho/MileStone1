//
// Created by alon on 16/12/2019.
//

#ifndef MILESTONE1__OPENSERVERCOMMAND_H_
#define MILESTONE1__OPENSERVERCOMMAND_H_
#include <string>
#include "Command.h"
#include <vector>

class OpenServerCommand : public Command{
 private:
  int client_socket;
  bool connected;


 public:
  OpenServerCommand();
  int execute(vector<string>* param, int index, SymbolTable* symt);
  void getData();
  bool isConnected();

  void getData(SymbolTable *symt);
};

#endif //MILESTONE1__OPENSERVERCOMMAND_H_
