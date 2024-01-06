//
// Created by johnj on 27/12/2023.
//

#ifndef BANKMANGMENTSYSTEM_USER_H
#define BANKMANGMENTSYSTEM_USER_H
#include<string>
#include <utility>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <thread>

class BankSystem;


class User {
protected:
    std::string m_userName;
    std::string m_hashedPassword;
    std::string m_salt;
    BankSystem* m_bankSystem =nullptr;
    std::string getTimeString();
    const int PAUSE_TIME=3;
    static void printInvalidInput(){std::cout<<"Invalid Input, Please Try Again";}
public:
    User(std::string userName,std::string passwordHash,std::string salt,BankSystem* bankSystem)
    : m_userName(std::move(userName)), m_hashedPassword(std::move(passwordHash)), m_salt(std::move(salt)),m_bankSystem(bankSystem) {}
    virtual ~User() =default;
    std::string getuserName() {return m_userName;}
    std::string getHashedPassword() {return m_hashedPassword;}
    std::string getSalt() {return m_salt;}
    void setUserName(std::string userName){m_userName= std::move(userName);}
    void setHashedPassword(std::string hashedPassword){m_hashedPassword= std::move(hashedPassword);}
    void setSalt(std::string salt){m_salt= std::move(salt);}
    virtual void printUserDetails();
    void changePassword(const std::shared_ptr<User>& user);
    friend std::ostream& operator<<(std::ostream& os,const User& user);

};



#endif //BANKMANGMENTSYSTEM_USER_H
