// Copyright [2013] <Copyright Young>
#include "Date.h"
#include <iostream>
#include "FileManage.h"
#include <string>
#include <list>
#include <fstream>

bool FileManage::instanceFlag_ = false;
FileManage* FileManage::instance_ = NULL;

FileManage::FileManage() {
    instanceFlag_ = true;
}

FileManage::~FileManage() {
    instanceFlag_ = false;
}

FileManage* FileManage::getInstance(void) {
    if (!instanceFlag_) {
        instance_ = new FileManage();
        instanceFlag_ = true;
        return instance_;
    } else {
        return instance_;
    }
}

std::list<User> FileManage::readUsersFromFile(void) {
    std::list<User> output;
    std::ifstream ifs("user.dat", std::ios_base::in);
    if (ifs.is_open()) {
        std::string name, password, email, phone;
        while (ifs >> name >> password >> email >> phone) {
            User temp(name, password, email, phone);
            output.push_back(temp);
        }
        return output;
    } else {
        std::list<User> temp;
        return temp;
    }
}

void FileManage::writeUsersToFile(std::list<User> users) {
    std::ofstream of("user.dat", std::ios_base::out);
    std::list<User>::iterator users_Iterator;
    std::string name, password, email, phone;
    for (users_Iterator = users.begin();
         users_Iterator != users.end();
         ++users_Iterator) {
         name = users_Iterator->getName();
         password = users_Iterator->getPassword();
         email = users_Iterator->getEmail();
         phone = users_Iterator->getPhone();
         of   << name << " "
              << password << " "
              << email << " "
              << phone << std::endl;
    }
}

std::list<Meeting> FileManage::readMeetingsFromFile(void) {
    std::list<Meeting> output;
    std::ifstream ifs("meeting.dat", std::ios_base::in);
    if (ifs.is_open()) {
        std::string sponsor, participator, title,
                   startTimestring, endTimestring;
        while (ifs >> sponsor >> participator 
                   >> startTimestring
                   >> endTimestring >> title) {
            Date startTime, endTime;
            startTime.stringToDate(startTimestring);
            endTime.stringToDate(endTimestring); 
            Meeting temp(sponsor, participator,
                         startTime, endTime, title);
            output.push_back(temp);
        }
        return output;
    } else {
        std::list<Meeting> temp;
        return temp;
    }
}

void FileManage::writeMeetingsToFile(std::list<Meeting> meetings) {
    std::ofstream of("meeting.dat", std::ios_base::out);
    std::list<Meeting> temp;
    temp = meetings;
    std::list<Meeting>::iterator meetings_Iterator;
    std::string sponsor, participator, title;
    Date startTime, endTime;
    if (!temp.empty()) {
        for (meetings_Iterator = meetings.begin();
        meetings_Iterator != meetings.end();
        ++meetings_Iterator) {
            sponsor = meetings_Iterator->getSponsor();
            participator = meetings_Iterator->getParticipator();
            startTime = meetings_Iterator->getStartDate();
            endTime = meetings_Iterator->getEndDate();
            title = meetings_Iterator->getTitle();
            of << sponsor << " "
               << participator << " "
               << startTime.dateToString(startTime) << " "
               << endTime.dateToString(endTime) << " "
               << title << std::endl;
        }
    } else {
    }
}

