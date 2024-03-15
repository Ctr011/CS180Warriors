#ifndef ERR_H
#define ERR_H

enum CODES{
    DMATCHES = 0, // Username and passwords do not match
    PMATCHES, //Passwords do not match
    REGNEG, // cannot Register account
    NFOUND, // Tags Not Found
    SUCCESS = 200, // OK
    FORBIDDEN = 403, // ERROR NOT ALLOWED
    NOTFOUND = 404 // CANNOT FIND REQUEST
};


#endif