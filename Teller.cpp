//
// Created by johnj on 27/12/2023.
//

#include "Teller.h"
#include "BankSystem.h"
#include "Customer.h"

void Teller::changeCustomersPassword(){
    std::string customerName;
    std::cout<<"Please enter the customers name:";
    std::cin >>customerName;
    std::shared_ptr<User> customer= m_bankSystem->getUser(customerName);
    if(std::dynamic_pointer_cast<Customer>(customer)){
        customer->changePassword(customer);
    }else
        std::cout << "User not found.\n";
}

void Teller::proccessTransaction(){
    std::cout << "Please enter the sender's userName: ";
    std::string sender;
    std::cin >> sender;
    std::shared_ptr<Customer> customer=  std::dynamic_pointer_cast<Customer>(m_bankSystem->getUser(sender));
    if(customer)
        customer->transaction(customer);
    else
        std::cout << "Couldn't find userName\n";
}


void Teller::printCustomerDetails(){
    std::cout << "Please enter the customer's userName: ";
    std::string customerUserName;
    std::cin >> customerUserName;
    std::shared_ptr<Customer> customer= std::dynamic_pointer_cast<Customer>(m_bankSystem->getUser(customerUserName));
    if(customer)
        customer->printUserDetails();
    else
        std::cout << "Couldn't find userName\n";
}