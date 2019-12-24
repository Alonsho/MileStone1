//
// Created by alon on 16/12/2019.
//

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <functional>
#include "OpenServerCommand.h"

using namespace std;

OpenServerCommand::OpenServerCommand() {
    connected = false;

}


int OpenServerCommand::execute(vector<string>* param, int index, SymbolTable* symt) {
    Interpreter* interp = symt->getInterpreter();



    Expression* e = interp->interpret((*param)[index]);
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(e->calculate());
    int addrlen = sizeof(address);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) < 0) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    client_socket = accept(socketfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        //  return -4;
    } else {
        cout<<"connected to simulator"<<std::endl;

    }

    close(socketfd); //closing the listening socket
    char buffer[1024] = {0};
    int valread = 1;
    valread = read( client_socket , buffer, 1024);
    connected = true;
    std::cout<<buffer<<std::endl << flush;
    getData(symt);



    return 2;
}

void OpenServerCommand::getData(SymbolTable* symt) {
    char buffer[1024] = {0};
    int valread = 1;
    while (!symt->isDone()) {
        valread = read( client_socket , buffer, 1024);
        string s(buffer);
        size_t pos = 0;
        size_t commaPos = 0;
        size_t prev = 0;
        string token;
        int i = 0;
        while (pos != string::npos) {
            pos = s.find("\n", pos);
            commaPos = s.find(",", commaPos);
            if (commaPos < pos) {
                token = s.substr(prev, commaPos-prev);
                prev = commaPos+1;
                symt->editSimArr(i, stod(token));
                i++;
            } else {
                token = s.substr(prev, pos-prev);
                prev = pos+1;
                symt->editSimArr(i, stod(token));
                i = 0;
            }
        }
        std::cout<<buffer<<std::endl << flush;
    }
}

bool OpenServerCommand::isConnected() {
    return connected;
}