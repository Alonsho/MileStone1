//
// Created by alon on 16/12/2019.
//

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <functional>
#include <thread>
#include <regex>
#include "OpenServerCommand.h"

using namespace std;

OpenServerCommand::OpenServerCommand() {

}


int OpenServerCommand::execute(vector<string>* param, int index, SymbolTable* symt) {
    Interpreter* interp = symt->getInterpreter();
    Expression* e = interp->interpret((*param)[index]);
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        delete e;
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

    //closing the listening socket
    close(socketfd);
    // receive first line of data, it will not be used for any purpose
    char buffer[1024] = {0};
    read( client_socket , buffer, 1024);
    string st = buffer;
    // once the first line arrives, continue the script and create an independent thread which
    // continuously receives data from the simulator
    thread(&OpenServerCommand::getData, this, symt).detach();
    delete e;
    return 2;
}


// receives data from the simulator and assigns the values to the matching variables if needed
void OpenServerCommand::getData(SymbolTable* symt) {
    char buffer[1024] = {0};
    string value;
    string dataLine;
    std::vector<std::string> values;
    std::string singleValue;
    std::istringstream valueStream;
    // continues as long as the script is running
    while (!symt->isDone()) {
        read(client_socket, buffer, 1024);
        dataLine = getLastLine(buffer);
        // checks if a bad message syntax was sent by simulator
        if (dataLine.empty()) {
            continue;
        }
        valueStream = istringstream(dataLine);
        // divide line by commas
        while (std::getline(valueStream, singleValue, ','))
        {
            values.push_back(singleValue);
        }
        // assign each value to the matching variable
        for (unsigned int i = 0; i < values.size(); i++) {
            symt->editSimArr(i, stod(values[i]));
        }
        values.clear();
    }
}


// gets the latest VALID line of data sent by the simulator
string OpenServerCommand::getLastLine(char* buffer) {
    // valid syntax of a full line of data
    regex lineSyntax("((-?)[0-9]+\\.([0-9]+,)){35}(-?)[0-9]+\\.([0-9])+");
    std::vector<std::string> dataLines;
    std::string singleLine;
    std::istringstream tokenStream(buffer);
    // split the string by data lines
    while (std::getline(tokenStream, singleLine, '\n'))
    {
        dataLines.push_back(singleLine);
    }
    // check which is the LATEST valid line and return it
    int i = dataLines.size();
    i--;
    for (;i >= 0; i--) {
        if (regex_match(dataLines[i], lineSyntax)) {
            return dataLines[i];
        }
    }
    // if no valid lines are found, return empty string
    return "";
}