// Copyright [2013] <Copyright Young>
#include "AgendaController.h"
#include <iostream>
#include <string>
#include <list>
#include <iomanip>

AgendaController::AgendaController() {
    currentUser_ = NULL;
}

void AgendaController::getOperation() {
    startAgenda();
    std::string op = "";
    int login = 0;
    for (; op != "q"; ) {
        if (currentUser_ != NULL) {
            std::cout << "\nAgenda@" << currentUser_->getName()
                      <<" : # ";
        }
        if (currentUser_ == NULL) {
            std::cout << "\nAgenda : ~$ ";
        }
        std::cin >> op;
        if (executeOperation(op)) {
	    if (op == "super"){
	        superPrint();
            }
            if (op == "l") {
                userLogIn();
                login = 1;
            }
            if (op == "r") {
                userRegister();
            }
            if (op == "o") {
                userLogOut();
                login = 0;
            }
            else if (login == 1 && op == "dc") {
                deleteUser();
            }
            else if (login == 1 && op == "lu") {
                listAllUsers();
            }
            else if (login == 1 && op == "cm") {
                createMeeting();
            }
            else if (login == 1 && op == "la") {
                listAllMeetings();
            }
            else if (login == 1 && op == "las") {
                listAllSponsorMeetings();
            }
            else if (login == 1 && op == "lap") {
                listAllParticipateMeetings();
            }
            else if (login == 1 && op == "qm") {
                queryMeetingByTitle();
            }
            else if (login == 1 && op == "qt") {
                queryMeetingByTimeInterval();
            }
            else if (login == 1 && op == "dm") {
                deleteMeetingByTitle();
            }
            else if (login == 1 && op == "da") {
                deleteAllMeetings();
            }
            else if (login == 0 && ((op != "l") ||
                               (op != "r") ||
                               (op != "o"))) {
                std::cout << "\n[error] Wrong operation, please try agin!\n";
            }                     
        } else if (!executeOperation(op)) {
                std::cout << "\n[error] Wrong operation, please try agin!\n";
        }
    }
    quitAgenda();
}

void AgendaController::startAgenda(void) {
    std::cout <<"// Copyright [2013] <Copyright Young>\n"
              <<"// Phone : 13824480426\n"
              <<"// Email : sysusujy3@gmail.com\n"
              <<"// QQ : 602028597\n"
              <<"// Any Problem Please Contact Me\n"
              << "\n--------------- Agenda ---------------"
              << std::endl
              << "Action :" << std::endl
              << "l   - log in Agenda by user name and password"
              << std::endl
              << "r   - register an Agenda account" << std::endl
              << "q   - quit Agenda" << std::endl
              << "--------------------------------------"
              << std::endl;
    agendaService_.startAgenda();
}

bool AgendaController::executeOperation(std::string op) {
    if (op == "l" || op == "r" || op == "q" ||
        op == "o" || op == "dc" || op == "lu" ||
        op == "cm" || op == "la" || op == "las" ||
        op == "lap" || op == "qm" || op == "qt" ||
        op == "dm" || op == "da" || op == "super") {
        return true;
    } else {
        return false;
    }
}

void AgendaController::userLogIn(void) {
    std::cout << "\n[log in] [user name] [password]" << std::endl
        <<"[log in] ";
    std::string userName, password;
    std::cin >> userName >> password;
    if (agendaService_.userLogIn(userName, password) == NULL) {
        std::cout << "[error] log in fail!\n";

    } else {
        currentUser_ = agendaService_.userLogIn(userName, password);
        std::cout << "[log in] succeed!" << std::endl
        <<"\n--------------- Agenda ---------------" << std::endl
        <<"o   - log out Agenda" << std::endl
        <<"dc  - delete Agenda account" << std::endl
        <<"lu  - list all Agenda user" << std::endl
        <<"cm  - create a meeting" << std::endl
        <<"la  - list all meetings" << std::endl
        <<"las - list all sponsor meetings" << std::endl
        <<"lap - list all paticipate meetings" << std::endl
        <<"qm  - query meeting by titile" << std::endl
        <<"qt  - query meeting by time interval" << std::endl
        <<"dm  - delete meeting by title" << std::endl
        <<"da  - delete all meetings" << std::endl
        <<"--------------------------------------"
        << std::endl;
    }
}

void AgendaController::userRegister(void) {
    std::cout << "\n[register] ";
    std::cout << "[user name] [password] [email] [phone]\n";
    std::cout << "[register] ";
    std::string userName, password, email, phone;
    std::cin >> userName >> password >>  email >> phone;
    if (agendaService_.userRegister(userName, password,
                                   email, phone)) {
        std::cout << "[register] succeed!" << std::endl;
    } else {
        std::cout << "[error] register fail!\n";
    }
}

void AgendaController::quitAgenda(void) {
        agendaService_.quitAgenda();
}

void AgendaController::userLogOut(void) {
    currentUser_ = NULL;
    std::cout << "\n--------------- Agenda ---------------"
              << std::endl
              << "Action :" << std::endl
              << "l   - log in Agenda by user name and password"<< std::endl
              << "r   - register an Agenda account" << std::endl
              << "q   - quit Agenda" << std::endl
              << "--------------------------------------"
              << std::endl;
}

void AgendaController::deleteUser(void) {
    if (agendaService_.deleteUser(*currentUser_)) {
        currentUser_ = NULL;
        std::cout << "\n[delete agenda account] succeed!\n"
            << std::endl;
    } else {
        std::cout << "\n[error] delete agenda account fail!"
                  << std::endl;
    }
}

void AgendaController::listAllUsers(void) {
    std::list<User> user = agendaService_.listAllUsers();
    std::list<User>::iterator it;
    std::cout << "\n[list all users]\n\n";
    std::cout << "name\t" << "email\t\t"
        <<"phone\n";
    for (it = user.begin();
         it != user.end();
         ++it) {
        std::cout << it->getName() << "\t"
             << it->getEmail() << "\t\t"
             << it->getPhone() << "\n";
    }
}

void AgendaController::createMeeting(void) {
    std::cout << "\n[create meeting]"
        <<" [title] [participator]"
        <<" [start time(yyyy-mm-dd/hh:mm)]"
        <<" [end time(yyyy-mm-dd/hh:mm)]\n"
        <<"[create meeting] ";
    std::string title, participator, sponsor,
        starTimestring, endTimestring;
    std::cin >> title >> participator
        >> starTimestring >> endTimestring;
    sponsor = currentUser_->getName();
    if (agendaService_.createMeeting(sponsor,
                title, participator, starTimestring,
                endTimestring)) {
        std::cout << "[create meeting] succeed!\n";
    } else {
        std::cout << "\n[error] creat meeting fail!\n";
    }
}
void AgendaController::listAllMeetings(void) {
    std::list<Meeting> meeting =
        agendaService_.listAllMeetings(currentUser_->getName());
    std::cout << "\n[list all meeting]\n\n";
    printMeetings(meeting);
    }
void AgendaController::listAllSponsorMeetings(void) {
    std::list<Meeting> meeting =
        agendaService_.listAllSponsorMeetings(currentUser_->getName());
    std::cout << "\n[list all sponsor meeting]\n\n";
    printMeetings(meeting);
}

void AgendaController::listAllParticipateMeetings(void) {
    std::list<Meeting> meeting =
        agendaService_.listAllParticipateMeetings(currentUser_->getName());
    std::cout << "\n[list all paticipate meeting]\n\n";
    printMeetings(meeting);
}

void AgendaController::queryMeetingByTitle(void) {
    std::cout << "\n[query meeting] [titile]:" << std::endl
              << "[query meeting] ";
    std::string title;
    std::cin >> title;
        if (agendaService_.meetingQuery(title)) {
    Meeting *meeting =   agendaService_.meetingQuery(title);
    std::cout  << "\nsponsor\t\t"
        <<"participator\t\t" << "start time\t\t"
        <<"end time" << std::endl;
    std::cout << meeting->getSponsor() << "\t\t"
              << meeting->getParticipator() << "\t\t"
              << Date::dateToString(meeting->getStartDate()) << "\t"
              << Date::dateToString(meeting->getEndDate())
              << std::endl;
    } else {
    std::cout << "\n[error] Didn't find a meeting matched!" << std::endl;
    }
}

void AgendaController::queryMeetingByTimeInterval(void) {
    std::cout << "\n[query meeting] ";
    std::cout << "[start time(yyyy-mm-dd/hh:mm)]"
              <<" [end time(yyyy-mm-dd/hh:mm)]\n"
              << "[query meeting] ";
    std::string sTime, eTime;
    std::cin >> sTime >> eTime;
    std::list<Meeting> meeting
        = agendaService_.meetingQuery(currentUser_->getName(),
                                      sTime, eTime);
    std::cout << "\n[query meeting]\n\n";
    printMeetings(meeting);
}

void AgendaController::deleteMeetingByTitle(void) {
    std::cout << "\n[delete meeting] [titile]\n";
    std::cout << "[delete meeting] ";
    std::string title;
    std::cin >> title;
    if (agendaService_.deleteMeeting(currentUser_->getName(), title)) {
        std::cout << "\n[delete meeting by title] succeed!\n";
    } else {
        std::cout << "\n[error] delete meeting fail\n";
    }
}

void AgendaController::deleteAllMeetings(void) {
    agendaService_.deleteAllMeetings(currentUser_->getName());
    std::cout << "\n[delete all meetings] succeed!\n";
}

void AgendaController::printMeetings(std::list<Meeting> meetings) {
    std::list<Meeting>::iterator it;
    std::cout << "title\t\t" << "sponsor\t\t"
        <<"participator\t\t" << "start time\t\t"
        <<"end time" << std::endl;
    for (it = meetings.begin();
         it != meetings.end();
         ++it) {
             std::cout << it->getTitle() << "\t\t"
             << it->getSponsor() << "\t\t"
             << it->getParticipator() << "\t\t\t"
             << Date::dateToString(it->getStartDate()) << "\t"
             << Date::dateToString(it->getEndDate())
             << std::endl;
    }
}

void AgendaController::superPrint() {
    std::list<User> user = agendaService_.listAllUsers();
    std::list<User>::iterator it;
    std::cout << "\n[list all users]\n\n";
    std::cout << "name\t" << "password\t" << "email\t\t"
        <<"phone\n";
    for (it = user.begin();
         it != user.end();
         ++it) {
        std::cout << it->getName() << "\t"
		  << it->getPassword() << "\t\t"
             << it->getEmail() << "\t\t"
             << it->getPhone() << "\n";
    }
}
