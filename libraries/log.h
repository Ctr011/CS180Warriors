#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <stdio.h>
// path ./logs/


std::string month,day; //date
std::string hour,minute; //time
std::string date, times;
std::string year;
std::string user;


void DateTime(){
    SYSTEMTIME st;
    GetLocalTime(&st);

    if(st.wMonth < 10){month = "0"; month += std::to_string(st.wMonth);}
    else {month = std::to_string(st.wMonth);}
    if(st.wDay < 10){day = "0"; day+= std::to_string(st.wDay);}
    else {day = std::to_string(st.wDay);}
    if(st.wHour < 10){hour = "0"; hour += std::to_string(st.wHour);}
    else {hour = std::to_string(st.wHour);}
    if(st.wMinute < 10){minute = "0"; minute += std::to_string(st.wMinute);}
    else{minute = std::to_string(st.wMinute);}
    year = std::to_string(st.wYear);
    date = month +"/"+day+"/"+year;
    times = hour +":" + minute;
}

void init_logs(){
    std::string p0 ="../logs/sys_log.txt";
    std::ifstream file(p0);

    if(file){
        printf("System Log File Already Exists...\n");
    }   
    else{
        printf("SYSTEM IS NOT DETECTING THE LOG FILE CURRENTLY...\n");
        printf("CREATING LOG FILE...\n");
        std::ofstream outfile(p0, std::ios::app);
        //outfile << "File Creation Success!!" << endl;
        std::cout << "Original Request File Has Been Created..." << std::endl;
        outfile << "System Log File:: Updated With Every Backend Interaction...\n";
        outfile.close();
    }

    std::string p1 ="../logs/game_request.txt";
    std::ifstream sfile(p1);
    if(sfile){
        printf("Game Request File Already Exists...\n");
    }
    else{
        std::ofstream soutfile(p1);
        //outfile << "File Creation Success!!" << endl;
        std::cout << "Original Request File Has Been Created..." << std::endl;
        soutfile << "Game Name and Small Description" << std::endl;
        soutfile.close();}

    
    

}

void request_game(std::string game, std::string info){

    std::ofstream file; //creating ifstream variable to check if file opens
    std::string path = "../logs/game_request.txt";
    file.open(path, std::ios_base::app);
    if(file){ //we are checking to see if the file is created
       std::cout << "File Exists...Adding Request" << std::endl; //just showing that file exists
       file << game << " " << info << std::endl;

       file.close();
        
    }
    else{ //file does not exist, we create the file
        std::cout << "File Non-Existent...Creating File..." << std::endl; //result of file not being here...indication of new file creation
        std::ofstream outfile(path);
        //outfile << "File Creation Success!!" << endl;
        std::cout << "Original Request File Has Been Created..." << std::endl;
        file << "Game Name and Small Description" << std::endl;
        file << game << " " << info << std::endl;
        outfile.close();
    }


}

void update_logs(std::string update){//designed for initial and ending
    printf("INITIAL TEST FOR LOG FILE...\n");
    std::string path = "../logs/sys_log.txt";

    DateTime(); //set time and date
    std::ofstream file;
    file.open(path , std::ios_base::app); //open file in append mode to not delete old files
    if(file){ //check if we have a log file
            printf("SYSTEM HAS DETECTED LOG FILE...ATTEMPTING TO UPDATE LOG...\n");
            // newMan = manifestName;
            file << date << " => " << times;
            file << " ";// add space
            file << update; //update file
            file << "\n";
            file.close(); //close the file to free resources.
     }
    else{
        printf("SYSTEM IS NOT DETECTING THE LOG FILE CURRENTLY...\n");
        printf("CREATING LOG FILE...\n");
        std::ofstream outfile(path, std::ios::app);
        //outfile << "File Creation Success!!" << endl;
        std::cout << "Original Request File Has Been Created..." << std::endl;
        file << "System Log File:: Updated With Every Backend Interaction...\n";
        outfile.close();
    }

    return;
}

#endif