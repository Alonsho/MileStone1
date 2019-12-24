//
// Created by alon on 17/12/2019.
//

#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "Interpreter.h"

int ConnectCommand::execute(vector<string>* param, int index, SymbolTable* symt) {
    Interpreter* interp = symt->getInterpreter();
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    string str = (*param)[index].substr(1, (*param)[index].size() - 2);
    char ip[str.size() + 1];
    strcpy(ip, (*param)[0].c_str());
    index++;
    Expression* e = interp->interpret((*param)[index]);

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(e->calculate());
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
        connected = true;
    }
    sendData(symt);
    //if here we made a connection
    char hello[] = "set /controls/flight/rudder -1\r\n";
    ///
    //SEND THE SERVER IF A VARIABLE VALUE HAS BEEN CHANGED (AND THE ARROW POINTS RIGHT) (MAYBE IN A SEPERATE FUNCTION)
    int is_sent = send(client_socket , hello , strlen(hello) , 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"Hello message sent to server" <<std::endl;
    }

    char buffer[1024] = {0};
    int valread = read( client_socket , buffer, 1024);

    std::cout<<buffer<<std::endl << flush;

    close(client_socket);
    return 3;
}

bool ConnectCommand::isConnected() {
    return connected;
}


void ConnectCommand::sendData(SymbolTable* symt, int client_socket) {
    queue <string> q = symt->getQueue();
    while (!symt->isDone()) {
        if (q.size() != 0) {
            string toSend = q.pop();
            int is_sent = send(client_socket , toSend , strlen(toSend) , 0);
            if (is_sent == -1) {
                std::cout<<"Error sending message"<<std::endl;
            }
        }
        sleep(1);
    }
}

