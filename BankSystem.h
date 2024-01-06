//
// Created by johnj on 27/12/2023.
//

#ifndef BANKMANGMENTSYSTEM_BANKSYSTEM_H
#define BANKMANGMENTSYSTEM_BANKSYSTEM_H
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <memory>


class User;
class Customer;
class Teller;
class Manger;


class BankSystem {
private:
    std::unordered_map<std::string,std::shared_ptr<Customer>> m_customerDatabase;
    std::unordered_map<std::string,std::shared_ptr<Teller>> m_tellerDatabase;
    std::shared_ptr<Manger> m_manger = nullptr;

     const int CUSTOMER_VARIABLE_NUMBER = 4;
     const int VARIABLE_NUMBER = 3;
     const int PAUSE_TIME =3;

     std::string genSalt();
     std::string sha256(const std::string& input);
    std::shared_ptr<User> registerUser(const std::string& userName, const std::string& password);
     std::string hash(const std::string& password,const std::string& salt);
    void saveToFile();
    void loadFromFile();
    void registerCostumer(const std::string& userName, const std::string& password);
    void registerTeller(const std::string& userName, const std::string& password);
    void registerManger(const std::string& userName, const std::string& password);

public:
    BankSystem() {loadFromFile();}
    ~BankSystem() {saveToFile();}
    void addCustomerAccount();
    void addTellerAccount();
    void replaceManger();
    void deleteCustomer();
    bool deleteTeller(const std::string& currentUserName);
    void transaction(const std::shared_ptr<Customer>& from,const std::string& to,double amount);
    std::shared_ptr<User> authinticate(const std::string& userName, const std::string& password);
    bool searchCustomer(const std::string& userName);
    bool searchTeller(const std::string& userName);
    bool isThereAManger(){return m_manger != nullptr;}
    void changePassword(const std::shared_ptr<User>& user,const std::string& newPassword);
    std::shared_ptr<User> getUser(const std::string& userName);
    const std::unordered_map<std::string,std::shared_ptr<Customer>>& getCustomers(){return m_customerDatabase;}
    const std::unordered_map<std::string,std::shared_ptr<Teller>>& getTellers(){return m_tellerDatabase;}

};

#endif //BANKMANGMENTSYSTEM_BANKSYSTEM_H
