// Copyright [2013] <Copyright Young>
#include "AgendaService.h"
#include <stdio.h>
#include <string>
#include <list>
#include <iostream>

AgendaService::AgendaService() {
    userManage_ = UserManage::getInstance();
    meetingManage_ = MeetingManage::getInstance();
    fileManage_ = FileManage::getInstance();
}

AgendaService::~AgendaService() {
    delete userManage_;
    delete meetingManage_;
    delete fileManage_;
}

User* AgendaService::userLogIn(std::string userName, std::string password) {
    if (userManage_->findUserByName(userName)) {
        if ((userManage_->findUserByName(userName))
                ->getPassword() == password)
            return userManage_->findUserByName(userName);
    } else {
        User *temp = NULL;
        return temp;
    }
}

bool AgendaService::userRegister(std::string userName, std::string password,
                                 std::string email, std::string phone) {
    return userManage_->createUser(userName, password, email, phone);
}

bool AgendaService::deleteUser(User user) {
  std::list<Meeting> meeting;
  meeting = listAllMeetings(user.getName());
  if (meeting.empty()) {
      return userManage_->deleteUser(user);
  } else {
      return false;
  }
}

std::list<User> AgendaService::listAllUsers(void) {
    return (userManage_->listAllUsers());
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                                  std::string participator,
                                  std::string startDate, std::string endDate) {
    if (userManage_->findUserByName(participator) == 0)
        return false;
    if (((userManage_->findUserByName(userName))->getName() == userName) &&
        ((userManage_->findUserByName(participator))->getName() ==
          participator)) {
        Date sTime, eTime;
        sTime = Date::stringToDate(startDate);
        eTime = Date::stringToDate(endDate);
        return meetingManage_->addMeeting(userName, participator,
                                      sTime, eTime, title);
    } else {
        return false;
    }
}

Meeting* AgendaService::meetingQuery(std::string title) {
    return meetingManage_->queryMeetingByTitle(title);
}

    std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                       std::string startDate,
                                       std::string endDate) {
    Date sTime, eTime;
    sTime = Date::stringToDate(startDate);
    eTime = Date::stringToDate(endDate);
    return meetingManage_->queryMeetingsByTime(userName, sTime, eTime);
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    return meetingManage_->listAllMeetings(userName);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    return meetingManage_->listAllSponsorMeetings(userName);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(
                                         std::string userName) {
    return meetingManage_->listAllParticipateMeetings(userName);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    return meetingManage_->deleteMeeting(userName, title);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    std::list<Meeting> temp;
    temp = listAllMeetings(userName);
    if (temp.empty()) {
        return true;
    } else {
        return meetingManage_->deleteAllMeetings(userName);
    }
}

void AgendaService::startAgenda() {
    userManage_->initUsersList(fileManage_->readUsersFromFile());
    meetingManage_->initMeetingsList(fileManage_->readMeetingsFromFile());
}

void AgendaService::quitAgenda() {
  if (remove("user.dat") && remove("meeting.dat")) {
    puts("I Am Sorry, Something Wrong In Saving Date\n");
    puts("Please Contact The Author!");
  } else {
        fileManage_->writeUsersToFile(userManage_->listAllUsers());
        fileManage_->writeMeetingsToFile(meetingManage_->acquireMeetingsList());
        puts("\n--------------Quiting Agenda--------------");
        puts("Date Has Been Saved Successfully!");
        puts("Have A Nice Day!");
        puts("By Young");
        puts("------------------------------------------\n");
  }
}
