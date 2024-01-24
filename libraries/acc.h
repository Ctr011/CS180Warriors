#ifndef ACC_H
#define ACC_H

/*
    C++ Libraries used for account creation
*/
#include <iostream>
#include <filesystem>
#include <string>

void AddPass(std::string);
void AddEmail(std::string);
bool CheckEmailoPass(std::string, std::string);

#endif