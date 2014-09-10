// Copyright [2013] <Copyright Young>
#include "User.h"
#include <string>

User::User() {
}

User::User(std::string userName, std::string userPassword,
           std::string userEmail, std::string userPhone) {
    name_ = userName;
    password_ = userPassword;
    email_ = userEmail;
    phone_ = userPhone;
}

std::string User::getName() {
    return name_;
}

void User::setName(std::string name) {
    name_ = name;
}

std::string User::getPassword() {
    return password_;
}

void User::setPassword(std::string password) {
    password_ = password;
}

std::string User::getEmail() {
    return email_;
}

void User::setEmail(std::string email) {
    email_ = email;
}

std::string User::getPhone() {
    return phone_;
}

void User::setPhone(std::string phone) {
    phone_ = phone;
}
