#include <iostream> //initial library
#include <fstream> //allows for txt file reading and writing
#include <sstream> //allows for txt file reading and writing
#define NOMIMAX //fixes threading problem created by the windows and websocket libraries
#include <WinSock2.h> //allows for server interaction with the webpages
#include <Windows.h> //allows us to use windows api to interact with the server
#include <string>
#include <filesystem> //allows us to check and see where the server is located

//Created Libraries
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
    //initializing the server to sv
    httplib::Server sv;

    //setting first mount for files
    sv.set_mount_point("/", "../webpage");

    //setting the directory for HTML files
    sv.set_base_dir("../webpage/HTML");

    //setting the mount points for specific file extensions (JS, CSS, HTML)
    sv.set_mount_point("/JS", "../webpage/JS");
    sv.set_mount_point("/CSS", "../webpage/CSS");
    sv.set_mount_point("HTML", "../webpage/HTML");

    //setting functiom to evoke html files
    sv.Get("/", [](const httplib::Request &, httplib::Response &resp){
        std::ifstream file("../webpage/HTML/temp_intro.html"); //change later on with actual intro page
        std::stringstream buffer; //setting buffer for the html files
        buffer << file.rdbuf(); //buffer will now load the html file (webpage)
        resp.set_content(buffer.str(), "text/html"); //finally loading the file page onto the server 
    });

    //intital test for the server
    sv.Get("/hi", [](const httplib::Request &, httplib::Response &res) { 
        res.set_content("Hello World!", "text/plain");
    });

    //setting starting server comment 
    std::cout << "Server is listening to Port 8080..." << std::endl;

    //opening the port for the server
    sv.listen("localhost" , 8080);
}
