//
// Created by johnj on 27/12/2023.
//

#ifndef BANKMANGMENTSYSTEM_CUSTOMER_H
#define BANKMANGMENTSYSTEM_CUSTOMER_H
#include <string>
#include "User.h"

class BankSystem;

class Customer : public User {
private:
    double m_balance=0;


public:
    explicit  Customer(const std::string& userName,const std::string& hashedPassword,const std::string& salt,BankSystem* bankSystem,double balance):
    User(userName,hashedPassword,salt,bankSystem),m_balance(balance){}
    explicit Customer(const User& user): User(user){}
    void withDraw();

    void deposit();

    void printUserDetails() override;

    void transactiontSent(double amount);

    void transactionRecevied(double amount);

    void transaction(const std::shared_ptr<Customer>& customer);

    double getBalance(){return m_balance;}
};


#endif //BANKMANGMENTSYSTEM_CUSTOMER_H
