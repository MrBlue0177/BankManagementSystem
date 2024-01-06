//
// Created by johnj on 27/12/2023.
//

#ifndef BANKMANGMENTSYSTEM_TELLER_H
#define BANKMANGMENTSYSTEM_TELLER_H

#include "User.h"

class Customer;

class Teller : public User {
private:

public:
    explicit Teller(const User& user) : User(user){};
    explicit  Teller(const std::string& userName, const std::string& hashedPassword,const std::string& salt,BankSystem* bankSystem):
    User(userName,hashedPassword,salt,bankSystem){}
    void changeCustomersPassword();
    void proccessTransaction();
    void printCustomerDetails();
};


#endif //BANKMANGMENTSYSTEM_TELLER_H
