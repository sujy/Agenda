// Copyright [2013] <Copyright Young>
#include "MeetingManage.h"
#include <string>
#include <list>
#include <iostream>

bool MeetingManage::instanceFlag_ = false;
MeetingManage* MeetingManage::instance_ = NULL;

MeetingManage::MeetingManage() {
    instanceFlag_ = true;
};

MeetingManage::~MeetingManage() {
    instanceFlag_= false;
}

MeetingManage* MeetingManage::getInstance() {
    if (!instanceFlag_) {
        instance_ = new MeetingManage();
        instanceFlag_ = true;
        return MeetingManage::instance_;
    } else {
        return MeetingManage::instance_;
    }
}

void MeetingManage::initMeetingsList(std::list<Meeting> meetings) {
    meetings_.assign(meetings.begin(), meetings.end());
}


std::list<Meeting> MeetingManage::acquireMeetingsList(void) {
    return meetings_;
}

bool MeetingManage::addMeeting(std::string sponsor, std::string participator,
                               Date stime, Date etime, std::string title) {
    std::list<Meeting>::iterator meetings_Iterator;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
            if ((meetings_Iterator->getStartDate() < etime) &&
                (meetings_Iterator->getStartDate() > stime))
                return false;
            if ((meetings_Iterator->getEndDate() < etime) &&
                (meetings_Iterator->getStartDate() > stime))
                return false;
            if ((meetings_Iterator->getEndDate() >= etime) &&
                (meetings_Iterator->getStartDate() <= stime))
                return false;
            if ((meetings_Iterator->getEndDate() <= etime) &&
                (meetings_Iterator->getStartDate() >= stime))
                return false;
            if (stime >= etime)
                return false;
            if (queryMeetingByTitle(title))
                return false;
    }
    Meeting addMeeting(sponsor, participator, stime, etime, title);
    meetings_.push_back(addMeeting);
    return true;
}

bool MeetingManage::deleteMeeting(std::string userName, std::string title) {
    std::list<Meeting>::iterator meetings_Iterator;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
            if ((meetings_Iterator->getParticipator() == userName) ||
                (meetings_Iterator->getSponsor() == userName)) {
                if (meetings_Iterator->getTitle() == title) {
                    meetings_.erase(meetings_Iterator);
                    return true;
                }
            }
    }
    return false;
}

bool MeetingManage::deleteAllMeetings(std::string userName) {
    std::list<Meeting>::iterator meetings_Iterator;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if ((meetings_Iterator->getSponsor() == userName) ||
            (meetings_Iterator->getParticipator() == userName))
            meetings_.erase(meetings_Iterator);
    }
    return true;
}

bool MeetingManage::updateMeetingParticipator(std::string title,
                                              std::string newParticipator) {
    std::list<Meeting>::iterator meetings_Iterator;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if (meetings_Iterator->getTitle() == title) {
            meetings_Iterator->setParticipator(newParticipator);
            return true;
        }
    }
    return false;
}

bool MeetingManage::updateMeetingStartDate(std::string title,
                                           Date newStartDate) {
    std::list<Meeting>::iterator meetings_Iterator;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if (meetings_Iterator->getTitle() == title) {
            meetings_Iterator->setStartDate(newStartDate);
            return true;
        }
    }
    return false;
}

bool MeetingManage::updateMeetingEndDate(std::string title, Date newEndDate) {
    std::list<Meeting>::iterator meetings_Iterator;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if (meetings_Iterator->getTitle() == title) {
            meetings_Iterator->setEndDate(newEndDate);
            return true;
        }
    }
    return false;
}

Meeting* MeetingManage::queryMeetingByTitle(std::string title) {
    std::list<Meeting>::iterator meetings_Iterator;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if (meetings_Iterator->getTitle() == title) {
            return &*meetings_Iterator;
        }
    }
    Meeting *temp = NULL;
    return temp;
}

std::list<Meeting> MeetingManage::queryMeetingsByTime(std::string userName,
                                                 Date stime,
                                                 Date etime) {
    std::list<Meeting>::iterator meetings_Iterator;
    std::list<Meeting> newlist;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if (meetings_Iterator->getSponsor() == userName ||
            meetings_Iterator->getParticipator() == userName) {
            if (meetings_Iterator->getStartDate() > stime &&
                meetings_Iterator->getEndDate() < etime) {
                newlist.push_back(*meetings_Iterator);
            }
        }
    }
    return newlist;
}

std::list<Meeting> MeetingManage::listAllMeetings(std::string userName) {
    std::list<Meeting>::iterator meetings_Iterator;
    std::list<Meeting> newlist;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if (meetings_Iterator->getSponsor() == userName ||
           meetings_Iterator->getParticipator() == userName) {
            newlist.push_back(*meetings_Iterator);
        }
    }
    return newlist;
}

std::list<Meeting> MeetingManage::listAllSponsorMeetings(std::string userName) {
    std::list<Meeting>::iterator meetings_Iterator;
    std::list<Meeting> newlist;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if (meetings_Iterator->getSponsor() == userName) {
            newlist.push_back(*meetings_Iterator);
        }
    }
    return newlist;
}

std::list<Meeting> MeetingManage::listAllParticipateMeetings
                                  (std::string userName) {
    std::list<Meeting>::iterator meetings_Iterator;
    std::list<Meeting> newlist;
    for (meetings_Iterator = meetings_.begin();
         meetings_Iterator != meetings_.end();
         ++meetings_Iterator) {
        if (meetings_Iterator->getParticipator() == userName) {
            newlist.push_back(*meetings_Iterator);
        }
    }
    return newlist;
}

