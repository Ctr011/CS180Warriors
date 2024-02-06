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
#include "../libraries/err.h"
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
        
    Another library we ended up using is localtunnel. This allows us to make the server visible to the local network without much tinkering with our 
    own firewall settings. The code runs on Node.js to work and creates an instance of the local host on a temp page. This page then sends back responses
    to the computer so it can do something with in. In our current state, it just checks inputs.

    LocalTunnel Github: https://github.com/localtunnel/localtunnel?tab=readme-ov-file
    Official Page: https://theboroer.github.io/localtunnel-www/
    Password for port: https://loca.lt/mytunnelpassword

    You only use this link on the host computer. Otherwise, just send the password onto the system

*/

int main(){
    //initializing the server to sv
    httplib::Server sv;
    std::string username;
    std::string password;
    std::string pass;
    std::string name;

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
        std::ifstream file("../webpage/HTML/introindex.html"); //change later on with actual intro page
        std::stringstream buffer; //setting buffer for the html files
        buffer << file.rdbuf(); //buffer will now load the html file (webpage)
        resp.set_content(buffer.str(), "text/html"); //finally loading the file page onto the server 
    });

    //intital test for the server
    sv.Get("/hi", [](const httplib::Request &, httplib::Response &resp) { 
                std::ifstream file("../webpage/HTML/temp_intro.html"); //change later on with actual intro page
        std::stringstream buffer; //setting buffer for the html files
        buffer << file.rdbuf(); //buffer will now load the html file (webpage)
        resp.set_content(buffer.str(), "text/html"); //finally loading the file page onto the server 
        // res.set_content("Hello World!", "text/plain");
    });

    sv.Post("/login", [](const httplib::Request &req, httplib::Response &resp){
        if(req.has_file("user") && req.has_file("user_pass")){
            const auto &username = req.get_file_value("user");
            const auto &password = req.get_file_value("user_pass");
            std::cout << "USERNAME: " << username.content << std::endl;
            std::cout << "PASSWORD: " << password.content << std::endl; //comment out later
            resp.status=SUCCESS;
            resp.set_content("ACCOUNT FOUND", "text/plain");
            return;
        }
        else{
        resp.status = 400;
        resp.set_content("USERNAME or PASSWORD NOT FOUND","text/plain");
        return;}
    });

    sv.Post("/register", [] (const httplib::Request &req, httplib::Response &resp){
        if(req.has_file("name") && req.has_file("user") && req.has_file("user_pass") && req.has_file("pass")){
            const auto &username = req.get_file_value("user");
            const auto &password = req.get_file_value("user_pass");
            const auto &name = req.get_file_value("name");
            const auto &pass = req.get_file_value("pass");
            std::cout << "NAME: " << name.content << std::endl; //comment out later
            std::cout << "USERNAME: " << username.content << std::endl;
            std::cout << "PASSWORD: " << password.content << std::endl; //comment out later
            std::cout << "PASS: " << pass.content << std::endl;
            if(password.content == pass.content){
                resp.status=SUCCESS;
            }
            else {
                resp.status = PMATCHES;
            }
            resp.set_content("USER REGISTERED", "text/plain");
            return;
        }
        else{
            resp.status = 400;
            resp.set_content("USER NOT REGISTERED", "text/plain");
            return;}
    });

    //setting starting server comment 
    std::cout << "Server is listening to Port 8080..." << std::endl;

    //opening the port for the server
    sv.listen("localhost" , 8080);
}
