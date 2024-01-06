//
// Created by johnj on 27/12/2023.
//

#include "User.h"
#include "BankSystem.h"


void User::printUserDetails(){
    std::cout << "UserName: " << this->m_userName << std::endl;
    std::cout << "Password: "<<this->m_hashedPassword << std::endl;
}

std::string User::getTimeString(){
    // Get the current time point
    auto currentTimePoint = std::chrono::system_clock::now();

    // Convert the current time point to a time_t
    std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);

    // Convert the current time to a string
    char timeString[100]; // Allocate a buffer for the string
    std::strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));

    return timeString;
}

void User::changePassword(const std::shared_ptr<User>& user) {
    std::cout << "please enter a new password:";
    std::string newPassword;
    std::cin >> newPassword;
    m_bankSystem->changePassword(user,newPassword);
    std::cout <<"\npassword changed successfully\n";
}

std::ostream& operator<<(std::ostream& os,const User& user){
    os << user.m_userName;
    return os;
}