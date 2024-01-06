//
// Created by johnj on 27/12/2023.
//

#include "Manger.h"
#include "Teller.h"
#include "BankSystem.h"
#include "Customer.h"

void Manger::changeTellerPassword(){
    std::string tellerName;
    std::cout<<"Please enter the teller's name:";
    std::cin >> tellerName;
    std::shared_ptr<User> teller= m_bankSystem->getUser(tellerName);
    if(std::dynamic_pointer_cast<Teller>(teller)){
        teller->changePassword(teller);
    }else
        std::cout << "User not found.\n";
}

void Manger::printCustomers(){
    const auto& customers = m_bankSystem->getCustomers();
    for(const auto& customer : customers){
        std::cout << *(customer.second) << "\n";
    }
}


void Manger::printTellers(){
    const auto& tellers = m_bankSystem->getTellers();
    for(const auto& teller : tellers){
        std::cout << *(teller.second) << "\n";
    }
}



