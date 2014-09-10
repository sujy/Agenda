// Copyright [2013] <Copyright Young>
#include "Date.h"
#include <sstream>
#include <string>

Date::Date() {
    year_ = 1000;
    month_ = 1;
    day_ = 1;
    hour_ = 0;
    minute_ = 0;
}

Date::Date(int year, int month, int day, int hour, int minute) {
    year_ = year;
    month_ = month;
    day_ = day;
    hour_ = hour;
    minute_ = minute;
}

int Date::getYear(void) const {
    return year_;
}

void Date::setYear(int year) {
    year_ = year;
}

int Date::getMonth(void) const {
    return month_;
}

void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay(void) const {
    return day_;
}

void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour(void) const {
    return hour_;
}

void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute(void) const {
    return minute_;
}

void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = date.getYear();
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        monthDay[1] += 1;
    }

    if (date.getYear() > 9999 || date.getYear() < 1000)
        return false;
    else if (date.getMonth() > 12 || date.getMonth() < 1)
        return false;
    else if ((date.getDay() > monthDay[date.getMonth() - 1])
             || (date.getDay() < 1))
        return false;
    else if (date.getHour() >= 24 || date.getHour() < 0)
        return false;
    else if (date.getMinute() >= 60 || date.getMinute() < 0)
        return false;
    else
        return true;
}

Date Date::stringToDate(std::string dateString) {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    char sign[4];
    std::stringstream input(dateString);
    input >> year >> sign[0]
          >> month >> sign[1]
          >> day >> sign[2]
          >> hour >> sign[3]
          >> minute;
    input.clear();
    Date temp(year, month, day, hour, minute);
    return temp;
}

std::string Date::dateToString(Date date) {
    int year = date.getYear();
    int month = date.getMonth();
    int day = date.getDay();
    int hour = date.getHour();
    int minute = date.getMinute();
    std::stringstream output;
    output << year << "-";
    if (month >= 10) {
        output << month << "-";
    } else {
        output << "0" << month << "-";
    }
    if (day >= 10) {
        output << day << "/";
    } else {
        output << "0" << day << "/";
    }
    if (hour >= 10) {
        output << hour << ":";
    } else {
        output << "0" << hour << ":";
    }
    if (minute >= 10) {
        output << minute;
    } else {
        output << "0" << minute;
    }
    return output.str();
}

Date &Date::operator=(const Date& date) {
    this->setYear(date.getYear());
    this->setMonth(date.getMonth());
    this->setDay(date.getDay());
    this->setHour(date.getHour());
    this->setMinute(date.getMinute());
    return *this;
}

bool Date::operator==(const Date& date) const {
        if (this->year_ == date.getYear() &&
        this->month_ == date.getMonth() &&
        this->day_ == date.getDay() &&
        this->hour_ == date.getHour() &&
        this->minute_ == date.getMinute())
        return true;
    else
        return false;
}

int transfer(int year, int month, int day, int hour, int minute) {
    int output;
    output = year * 100000000 + month *
             1000000 + day * 10000 + hour *100 + minute;
    return output;
}

bool Date::operator>(const Date& date) const {
    int thistime;
    int compare;
    thistime = transfer(this->year_, this->month_,
                        this->day_, this->hour_, this->minute_);
    compare = transfer(date.getYear(), date.getMonth(),
                       date.getDay(), date.getHour(), date.getMinute());

    if (thistime > compare)
        return true;
    else
        return false;
}
bool Date::operator<(const Date& date) const {
    int thistime;
    int compare;
    thistime = transfer(this->year_, this->month_,
                        this->day_, this->hour_, this->minute_);
    compare = transfer(date.getYear(), date.getMonth(),
                       date.getDay(), date.getHour(), date.getMinute());

    if (thistime < compare)
        return true;
    else
        return false;
}
bool Date::operator>=(const Date& date) const {
    int thistime;
    int compare;
    thistime = transfer(this->year_, this->month_,
                        this->day_, this->hour_, this->minute_);
    compare = transfer(date.getYear(), date.getMonth(),
                       date.getDay(), date.getHour(), date.getMinute());

    if (thistime >= compare)
        return true;
    else
        return false;
}
bool Date::operator<=(const Date& date) const {
    int thistime;
    int compare;
    thistime = transfer(this->year_, this->month_,
                        this->day_, this->hour_, this->minute_);
    compare = transfer(date.getYear(), date.getMonth(),
                       date.getDay(), date.getHour(), date.getMinute());
    if (thistime <= compare)
        return true;
    else
        return false;
}
