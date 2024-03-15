#ifndef ACC_CPP
#define ACC_CPP
#include "acc.h"

/*
    This will run our server initialization process, we will check to see if the server's folders have been already generated.
    If the system cannot find the necessary information, it will attempt to generate it. This function should be able to create secret folders as
    we attempt to simulate an external server running 
*/
void account::init(){
    return;
}


/*
    account::CheckUserTPass(string, string) will check the database to see if the user is currently in the system, if they are
    not, we will send an error and display that the account username or password does not match. 
*/
bool account::CheckUserTPass(std::string n, std::string m){ 
    account t;
    t.ups = false;

    if(n == ""){

    }
    if(m == ""){}
    return t.ups;
}

#endif