#include <iostream>
#include "cpp-httplib/httplib.h"
/*
    For this project, we will be using an open source library for communication between our c++ server and the ports.
    The library is called CPP-HTTPLIB by yhirose.
    Author's github: https://github.com/yhirose
    Library's github: https://github.com/yhirose/cpp-httplib

    For the rest of the project, we will create our own functions. 

    To build the server you need to do the following:
        -> download Build Tools for VS 2022 (the following are instructions on how to do so https://code.visualstudio.com/docs/cpp/config-msvc)
        -> run the Developer Command prompt for VS 2022 
        -> run "code ."
        -> open file location of the root for the server (the folder before webserver)
        -> click on the server.cpp file
        -> debug the program using cl.exe (this will build the program)

    If an error occurs:
        -> open the .vscode folder 
        -> add the following line to the args section:
            + "/std:c++17" or "/std:c++20" (in future, we can use "/std:c++23")
        

*/

int main(){
    httplib::Client cli("localhost" , 8080);
    std::cout << "Client is listening for port 8080" << std::endl;
    // cli.set_proxy("host", 8080);
    if(auto res = cli.Get("/")){
        std::cout << "SERVER FOUND!" << std::endl;
        std::cout << "STATUS: " << res->status << std::endl;
        std::cout << "BODY: " << res->body << std::endl;
        cli.set_keep_alive(true);
        while(1);
    }
    else{ std::cout << "SERVER NOT FOUND!" << std::endl;}
    // auto res = cli.Get("/");
    // std::cout << "STATUS: " << res->status << std::endl;
    // std::cout << "BODY: " << res->body << std::endl;
}