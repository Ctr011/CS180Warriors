#include <iostream> //initial library
#include <fstream> //allows for txt file reading and writing
#include <sstream> //allows for txt file reading and writing
#define NOMIMAX //fixes threading problem created by the windows and websocket libraries
#include <WinSock2.h> //allows for server interaction with the webpages
#include <Windows.h> //allows us to use windows api to interact with the server
#include <string>
#include <filesystem> //allows us to check and see where the server is located

//Includes for SQLlite database. If there are build problems follow the instructions: https://www.tutorialspoint.com/sqlite/sqlite_quick_guide.htm
//Also be sure to include the sqlite3.c file in the same directory as the server.cpp file and add it to the build process in tasks.json as ["${fileDirname}\\sqlite3.c",]
//Lastly, be sure the callback function is added above main as described in the above tutorial and getting a SQlite viewer extension can make it easy to view the db.
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

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

// This callback function is so the SQL errors show in vscode when something goes wrong
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(){
    //initializing the server to sv
    httplib::Server sv;
    std::string username;
    std::string password;
    std::string pass;
    std::string name;

    //Create variables for database
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

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

            sqlite3 *db;
            char *zErrMsg = 0;
            int rc;
            int rx;
            const char* data = "Callback function called";
            sqlite3_stmt *st;
            rc = sqlite3_open("Database.db", &db);
            std::string sql = "SELECT USERNAME, PASSWORD from User where USERNAME = '"  + username.content + "'  AND PASSWORD = '" + password.content +"'";
            std::string sql1 = "SELECT USERNAME, PASSWORD from User";
            std::cout << sql << std::endl;
            //rc = sqlite3_exec(db, sql1.c_str(),callback,(void*)data, &zErrMsg);
            rx = sqlite3_exec(db, sql.c_str(),callback,(void*)data, &zErrMsg);
            std::cout << rc << std::endl;
            rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &st, nullptr); //outputs the table
            // if(sqlite3_step(st) != NULL){
            //     resp.status = SUCCESS;
            //     return;
            // }
            std::cout << rc << std::endl;
            if(rx == SQLITE_OK && (rc = sqlite3_step(st)) == SQLITE_ROW){            
                // rc = sqlite3_step(st); // initial step to check
                std::cout << rc << std::endl;
                std::cout << sqlite3_column_text(st,0) << std::endl; // checking to see if there is a username
                std::cout << sqlite3_column_text(st,1) << std::endl; // checking to see if there is a password 
                resp.status = SUCCESS;
                sqlite3_finalize(st); // Always finalize a statement when you're done with it
                resp.set_content("ACCOUNT FOUND", "text/plain");
                return;
            }
            // while(st){
            //     char user[100] = sqlite3_column_text(st,0);

            //     if(userr == user){
            //         resp.status = SUCCESS;
            //         resp.set_content("ACCOUNT FOUND", "text/plain");
            //         return;
            //     }
            // }
            resp.status = DMATCHES;
            resp.set_content("ACCOUNT NOT FOUND", "text/plain");
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

            sqlite3 *db;
            char *zErrMsg = 0;
            int rc;
            int rc_check;
            int rx;
            rc = sqlite3_open("Database.db", &db);
            std::string sql = "INSERT INTO User (NAME, USERNAME, PASSWORD) VALUES (?1, ?2, ?3);";
            std::string sql_check = "SELECT USERNAME, PASSWORD from User where USERNAME = '"  + username.content +"'";
            sqlite3_stmt* stmt; // will point to prepared stamement object
            sqlite3_stmt* st;
            sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, nullptr);       
            rc = sqlite3_prepare_v2(db, sql_check.c_str(), -1, &st, nullptr); //outputs the table
            std::string newName = name.content;
            std::string newUsername = username.content;
            std::string newPassword = password.content;

            sqlite3_bind_text(stmt, 1, newName.c_str(), newName.length(), SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, newUsername.c_str(), newUsername.length(), SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, newPassword.c_str(), newPassword.length(), SQLITE_STATIC);

            // sqlite3_step(stmt); // Check the return value below this call to see if it was successful
            // sqlite3_finalize(stmt); // Always finalize a statement when you're done with it

            std::cout << "NAME: " << name.content << std::endl; //comment out later
            std::cout << "USERNAME: " << username.content << std::endl;
            std::cout << "PASSWORD: " << password.content << std::endl; //comment out later
            std::cout << "PASS: " << pass.content << std::endl;
            if(rc == SQLITE_OK && sqlite3_step(st) != SQLITE_ROW){
            if(password.content == pass.content){
                sqlite3_step(stmt); // Check the return value below this call to see if it was successful
                sqlite3_finalize(stmt); // Always finalize a statement when you're done with it
                resp.status=SUCCESS;
            }
            else {
                resp.status = PMATCHES;
            }}
            else{resp.status = 0; // user does already exists
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

    /* Open database */
    rc = sqlite3_open("Database.db", &db);
    std::cout << "Code has opened database" << std::endl;

    if( rc ) {
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       std::cout << "Database open failed" << std::endl;
       return(0);
    } else {
       std::cout << "Opened database" << std::endl;
    }

    /* Create SQL statement */
    char sql[] = "CREATE TABLE User ("                           \
      "NAME                TEXT      PRIMARY KEY      NOT NULL," \
      "USERNAME            TEXT                       NOT NULL," \
      "PASSWORD            TEXT                       NOT NULL);";

    //SEE: https://github.com/sqlitebrowser/sqlitebrowser/wiki/Win64-setup-%E2%80%94-Step-8-%E2%80%94-Install-SQLite

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       std::cout << "Table create failed" << std::endl;
       sqlite3_free(zErrMsg);
    } else {
       std::cout << "Table created successfully" << std::endl;
    }

    char sql1[] = "CREATE TABLE Games ("                           \
      "NAME                TEXT      PRIMARY KEY      NOT NULL," \
      "Description         TEXT                       NOT NULL," \
      "Tags                TEXT                       NOT NULL);";

    rc = sqlite3_exec(db, sql1, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       std::cout << "Table create failed" << std::endl;
       sqlite3_free(zErrMsg);
    } else {
       std::cout << "Table created successfully" << std::endl;
    }


    sqlite3 *plite;
    sqlite3 *pFile; // connection to database
    sqlite3_backup *back; // object to backup data
    sqlite3 *pto; // copyy to
    sqlite3 *pfrom; // copy from
    rc = sqlite3_open("backup_data.db", &plite);
    rc = sqlite3_open("Database.db", &pFile);

    if(rc == SQLITE_OK){
      pfrom = (pFile);
      pto = plite;

      back = sqlite3_backup_init(pto, "main", pfrom, "main");
      // std::cout << back << std::endl;
      if(back){
         sqlite3_backup_step(back,-1);
         sqlite3_backup_finish(back);
      }
         rc = sqlite3_errcode(pto);}

    //opening the port for the server
    sv.listen("localhost" , 8080);
}
