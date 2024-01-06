//
// Created by johnj on 27/12/2023.
//

#include "Customer.h"
#include "BankSystem.h"

void Customer::withDraw(){
    system("cls");
    double amount;
    std::cout << "please enter the amount you want to withdraw:";
    if(!(std::cin >> amount) || amount<0){
        system("cls");
        printInvalidInput();
        std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
        this->withDraw();
    }
    std::ofstream  records("CustomerRecords/"+getuserName()+".txt",std::ios::app);

    records << "withdraw: " << amount << " date and time: " << getTimeString() <<"\n";
    records.close();
    m_balance-=amount;
    std::cout << amount << " withdrawn." << std::endl;
}

void Customer::deposit(){
    double amount;
    std::cout << "please enter the amount you want to deposit:";
    if(!(std::cin >> amount) || amount<0){
        system("cls");
        printInvalidInput();
        std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
        this->deposit();
    }
    std::ofstream  records("CustomerRecords/"+getuserName()+".txt",std::ios::app);

    records << "Deposited: " << amount << " date and time: " << getTimeString() <<"\n";
    records.close();
    m_balance += amount;
    std::cout << amount << " deposited." << std::endl;
}

void Customer::printUserDetails(){
User::printUserDetails();
std::cout << "Balance: " << m_balance <<std::endl<<std::endl;
std::cout << "records:\n";
std::ifstream  records("CustomerRecords/"+getuserName()+".txt");

if(records.is_open()){
   std::string line;
   while(std::getline(records,line)){
        std::cout <<line <<std::endl;
   }
   records.close();
   }else{
       std::cerr <<"no records found or there was a problem opining the file\n";
   }
}

void Customer::transactiontSent(double amount){
    std::ofstream  records("CustomerRecords/"+getuserName()+".txt",std::ios::app);

    records << "Sent: " << amount << " date and time: " << getTimeString() <<"\n";
    records.close();
    m_balance-=amount;
}

void Customer::transactionRecevied(double amount){
    std::ofstream  records("CustomerRecords/"+getuserName()+".txt",std::ios::app);

    records << "Received: " << amount << " date and time: " << getTimeString() <<"\n";
    records.close();
    m_balance+=amount;
}

void Customer::transaction(const std::shared_ptr<Customer>& customer){
    std::string to;
    double amount;
    std::cout << "enter the userName of the receiver:";
    std::cin >> to;
    std::cout << "\nenter the amount you want to send:";
    if(!(std::cin >> amount) || amount < 0 ){
        system("cls");
        printInvalidInput();
        std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
        return;
    }
    m_bankSystem->transaction(customer,to,amount);
    std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
}





