// Copyright [2013] <Copyright Young>
#include "UserManage.h"
#include <string>
#include <list>

bool UserManage::instanceFlag_ = false;
UserManage* UserManage::instance_ = NULL;

UserManage::UserManage() {
    instanceFlag_ = true;
}

UserManage::~UserManage() {
    instanceFlag_ = false;
}

UserManage* UserManage::getInstance(void) {
    if (!instanceFlag_) {
        instance_ = new UserManage();
        instanceFlag_ = true;
        return instance_;
    } else {
        return instance_;
    }
}

void UserManage::initUsersList(std::list<User> users) {
    users_.assign(users.begin(), users.end());
}

User* UserManage::findUserByName(std::string userName) {
    std::list<User>::iterator users_Iterator;
    for (users_Iterator = users_.begin();
         users_Iterator!= users_.end();
         ++users_Iterator) {
        if (users_Iterator->getName() == userName) {
            return &(*users_Iterator);
        }
    }
    return NULL;
}

bool UserManage::createUser(std::string userName, std::string userPassword,
                            std::string userEmail, std::string userPhone) {
    if (findUserByName(userName)) {
            return false;
    } else {
        User create(userName, userPassword, userEmail, userPhone);
        users_.push_back(create);
        return true;
    }
}

bool UserManage::deleteUser(User user) {
    std::list<User>::iterator users_Iterator;
    for (users_Iterator = users_.begin();
         users_Iterator!= users_.end();
         ++users_Iterator) {
        if (users_Iterator->getName() == user.getName()) {
            users_.erase(users_Iterator);
            return true;
        }
    }
    return false;
}

bool UserManage::updateUserPassword(User user, std::string newPassword) {
    std::list<User>::iterator users_Iterator;
    for (users_Iterator = users_.begin();
         users_Iterator!= users_.end();
         ++users_Iterator) {
        if (users_Iterator->getName() == user.getName()) {
            (*users_Iterator).setPassword(newPassword);
            return true;
        }
    }
    return false;
}

bool UserManage::updateUserEmail(User user, std::string newEmail) {
    std::list<User>::iterator users_Iterator;
    for (users_Iterator = users_.begin();
         users_Iterator!= users_.end();
         ++users_Iterator) {
        if (users_Iterator->getName() == user.getName()) {
            (*users_Iterator).setEmail(newEmail);
            return true;
        }
    }
    return false;
}

bool UserManage::updateUserPhone(User user, std::string newPhone) {
    std::list<User>::iterator users_Iterator;
    for (users_Iterator = users_.begin();
         users_Iterator!= users_.end();
         ++users_Iterator) {
        if (users_Iterator->getName() == user.getName()) {
            (*users_Iterator).setPhone(newPhone);
            return true;
        }
    }
    return false;
}

std::list<User> UserManage::listAllUsers(void) {
    return users_;
}
















