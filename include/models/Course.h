#pragma once 
#include <string>

struct Course
{
    int courseID;
    char courseName[50];
    char description[500];
    bool isDeleted;

// HELPER FUNCTIONS 

    void setCourseName(const std::string& name){
        strncpy(courseName, name.c_str(), sizeof(courseName) - 1);
        courseName[sizeof(courseName) - 1] = '\0';
    }

    void setDescription(const std::string& desc){
        strncpy(description, desc.c_str(), sizeof(description) - 1);
        description[sizeof(description) - 1] = '\0';
    }
};