//
// Created by johnj on 27/12/2023.
//

#ifndef BANKMANGMENTSYSTEM_MANGER_H
#define BANKMANGMENTSYSTEM_MANGER_H
#include "User.h"



class Manger : public User{

public:
    explicit Manger(const User& user) : User(user) {};
    explicit Manger(const std::string& userName,const std::string& hashedPassword,const std::string& salt,BankSystem* bankSystem):
    User(userName,hashedPassword,salt, bankSystem){}

    void changeTellerPassword();
    void printCustomers();
    void printTellers();
};


#endif //BANKMANGMENTSYSTEM_MANGER_H
