#ifndef ACC_H
#define ACC_H

/*
    C++ Libraries used for account creation
*/
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <vector>
#include <string>


class account{ // account class to access, alter, or confirm information
   public:
        void account::init();
        void account::AddPass(std::string);
        void account::AddUser(std::string);
        void account::ChangeUPass(std::string);
        bool account::CheckUserTPass(std::string, std::string);
        bool account::CheckUExist(std::string);

    private:
        std::string USERNAME; // username provided by the user
        std::string PASSWORD; // password provided by the user 
        std::string FIRSTLAST; // first and lastt name of the user, we will not do a background check on these individuals
        bool ups; //both user and password exist within our data set
        bool use; //username either exists or doesnt exist

};
// void init();
// void AddPass(std::string);
// void AddEmail(std::string);
// bool CheckEmailoPass(std::string, std::string);

#endif