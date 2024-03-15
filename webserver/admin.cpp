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

/*
    This file is for admins to add games and their information to the data base

*/

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;}


int main(){
     //Create variables for database
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
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
    std::string n;
    std::string o;
    std::string name;
    std::string description;
    std::string tags;
    std::cout << "Please type 'ADD' or 'A' to add data to video games..." << std::endl;
    bool l = true;
    bool f = false;
    while(l){
        if(f == false){
            std::cin >> n;
        }
         if((n == "ADD" || n == "A") && f == false ){
            std::cout << "Please Enter Game Name: ";
            std::cin>>name;

            
            std::cout << "Enter a small description of the game: ";
            // getline(std::cin, description);
            getline(std::cin, description);

            std::cout <<"Enter the tags seperated via ',': ";
            std::cin >> tags;

            rc = sqlite3_open("Database.db", &db);
            std::string sql = "INSERT INTO Games (NAME, Description, Tags) VALUES (?1, ?2, ?3);";
            std::string sql_check = "SELECT NAME from Games where NAME = '"  + name +"'";


            sqlite3_stmt* stmt; // will point to prepared stamement object
            sqlite3_stmt* st;
            sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, nullptr);       
            rc = sqlite3_prepare_v2(db, sql_check.c_str(), -1, &st, nullptr); //outputs the table


            sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, description.c_str(), description.length(), SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, tags.c_str(), tags.length(), SQLITE_STATIC);

            sqlite3_step(stmt); // Check the return value below this call to see if it was successful
            sqlite3_finalize(stmt); // Always finalize a statement when you're done with it

            // if(rc == SQLITE_OK && sqlite3_step(st) != SQLITE_ROW){
            //     sqlite3_step(stmt); // Check the return value below this call to see if it was successful
            //     sqlite3_finalize(stmt); // Always finalize a statement when you're done with it
            // }
            f = true;
         }
         else{std::cout << "HAVE NOT CHOSEN ADD/Aa..."<< std::endl;}

        if(f == true){
            std::cout << "Would you like to add more? Y/N: ";
            std::cin >> o;
            if(o == "Y" || o == "y"){
                f = false;
            }
            else if(o == "N" || o == "n"){
                f =  false;
                l = false;
                }
            else{
                std::cout << "HAVE NOT CHOSEN Y/N..." << std::endl;
                }
            }
    }
    return 0;
   }