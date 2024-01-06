//
// Created by johnj on 27/12/2023.
//

#include "BankSystem.h"
#include "User.h"
#include "Customer.h"
#include "Manger.h"
#include "Teller.h"


 std::string BankSystem::genSalt(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    // Generate a random salt
    std::string salt;
    for (int i = 0; i < 16; ++i) {
        salt += static_cast<char>(dis(gen));
    }
    return salt;
}

std::string BankSystem::sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)input.c_str(), input.length(), hash);

    // Clear sensitive information if needed

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

 std::string BankSystem::hash(const std::string& password,const std::string& salt){
    // Combine password and salt, then hash
    std::string saltedPassword = password + salt;
    return  sha256(saltedPassword);
}


std::shared_ptr<User> BankSystem::registerUser(const std::string& userName, const std::string& password){

    std::string salt = genSalt();

    std::string hashedPassword = hash(password,salt);
    return std::make_shared<User>(userName,hashedPassword,salt,this);
}

void BankSystem::registerCostumer(const std::string& userName,const std::string& password){
    auto user= registerUser(userName,password);
    m_customerDatabase[userName]= std::make_shared<Customer>(*user);
}

void BankSystem::registerTeller(const std::string& userName, const std::string& password){
    auto user= registerUser(userName,password);
    m_tellerDatabase[userName]= std::make_shared<Teller>(*user);
}

void BankSystem::registerManger(const std::string& userName, const std::string& password){
    auto user= registerUser(userName,password);
    m_manger= std::make_shared<Manger>(*user);
}

void BankSystem::deleteCustomer(){
    std::string userName;
    std::cout<<"Enter the userName of the account you want to delete:";
    std::cin >>userName;
    std::cout << std::endl;
    // Find the element with key 2
    auto it = m_customerDatabase.find(userName);

    // Check if the element is found before erasing
    if (it != m_customerDatabase.end()) {
        m_customerDatabase.erase(it);  // Erase the element using the iterator
        std::cout << "Customer " << userName << " removed." << std::endl;
    } else {
        std::cout << "Customer " << userName << " not found." << std::endl;
    }
}

bool BankSystem::deleteTeller(const std::string& currentUserName){
    std::string userName;
    std::cout<<"Enter the userName of the account you want to delete:";
    std::cin >>userName;
    std::cout << std::endl;
    auto it = m_tellerDatabase.find(userName);

    if(it != m_tellerDatabase.end()){
        m_tellerDatabase.erase(it);
        std::cout << "Teller " << userName << " removed." << std::endl;
    }else {
        std::cout << "Teller " << userName << " not found." << std::endl;
    }
    if(userName==currentUserName){
        return true;
    }
    return false;
}


void BankSystem::saveToFile(){
    std::ofstream outputCustomer("BankSystem/Customers.txt");
    if(outputCustomer.is_open()){
        for(const auto& data : m_customerDatabase){
            outputCustomer << data.second->getuserName() <<' ' <<data.second->getHashedPassword()<<' '<<data.second->getSalt()
            <<' '<<data.second->getBalance()<<"\n";
        }
    }else{
        std::cerr <<"couldn't open file:Customers.txt\n";
        exit(1);
    }
    std::ofstream outputTeller("BankSystem/Tellers.txt");
    if(outputTeller.is_open()){
        for(const auto& data : m_tellerDatabase){
            outputTeller << data.second->getuserName() <<' '<<data.second->getHashedPassword()<<' '<<data.second->getSalt()<<"\n";
        }
    }else{
        std::cerr <<"couldn't open file:Tellers.txt\n";
        exit(1);
    }
    std::ofstream outputManger("BankSystem/Manger.txt");
    if(outputManger.is_open()){
        outputManger<<m_manger->getuserName()<<' '<<m_manger->getHashedPassword()<<' '<<m_manger->getSalt()<<"\n";
    }else{
        std::cerr << "couldn't open file:Manger.txt\n";
        exit(1);
    }
}

void BankSystem::loadFromFile(){
    std::ifstream inputCustomer("BankSystem/Customers.txt");
    if(inputCustomer.is_open()){
        std::string line;
        while(std::getline(inputCustomer,line)){
            std::istringstream iss(line);
            std::string userName,hashedPassword,salt,balance;
            iss>>userName;
            iss>>hashedPassword;
            iss>>salt;
            iss>>balance;
            m_customerDatabase[userName]= std::make_shared<Customer>(userName,hashedPassword,salt,this,(double) std::stod(balance));
        }
    }else{
        std::cerr << "couldn't open file:Customers.txt\n";
        exit(1);
    }
    std::ifstream inputTeller("BankSystem/Tellers.txt");
    if(inputTeller.is_open()){
        std::string line;
        while(std::getline(inputTeller,line)){
            std::istringstream iss(line);
            std::string userName,hashedPassword,salt;
            iss>>userName;
            iss>>hashedPassword;
            iss>>salt;
            m_tellerDatabase[userName]= std::make_shared<Teller>(userName,hashedPassword,salt,this);
        }
    }else{
        std::cerr << "couldn't open file:Tellers.txt\n";
        exit(1);
    }
    std::ifstream inputManger("BankSystem/Manger.txt");
    if(inputManger.is_open()){
        std::string line;
        if(std::getline(inputManger,line)){
            std::istringstream iss(line);
            std::string userName,hashedPassword,salt;
            iss>>userName;
            iss>>hashedPassword;
            iss>>salt;
            m_manger = std::make_shared<Manger>(userName,hashedPassword,salt,this);
        }
    }else{
        std::cerr << "couldn't open file:Manger.txt\n";
        exit(1);
    }
}

void BankSystem::transaction(const std::shared_ptr<Customer>& from,const std::string& to,double amount){
    auto it = m_customerDatabase.find(to);
    if(it != m_customerDatabase.end()){
        from->transactiontSent(amount);
        it->second->transactionRecevied(amount);
        std::cout<< amount<<" sent to " << to << "successfully.\n";
    }else{
        std::cout <<"couldn't find user " << to << "\n";
    }
}

void BankSystem::changePassword(const std::shared_ptr<User>& user,const std::string& newPassword){
    user->setHashedPassword(hash(newPassword,user->getSalt()));
}

std::shared_ptr<User> BankSystem::authinticate(const std::string& userName, const std::string& password){
    auto itCustomer = m_customerDatabase.find(userName);
    if(itCustomer != m_customerDatabase.end() &&
            itCustomer->second->getHashedPassword() == hash(password, itCustomer->second->getSalt())){
        return itCustomer->second;
    }
    auto itTeller = m_tellerDatabase.find(userName);
    if(itTeller != m_tellerDatabase.end() && itTeller->second->getHashedPassword()==hash(password,itTeller->second->getSalt())){
        return itTeller->second;
    }
    if(m_manger && m_manger->getuserName() == userName && m_manger->getHashedPassword()==hash(password,m_manger->getSalt())){
        return m_manger;
    }
    return nullptr;
}

bool BankSystem::searchCustomer(const std::string& userName){
    auto it = m_customerDatabase.find(userName);
    if(it != m_customerDatabase.end())
        return true;
    return false;
}
bool BankSystem::searchTeller(const std::string& userName){
    auto it = m_tellerDatabase.find(userName);
    if(it != m_tellerDatabase.end())
        return true;
    return false;
}

std::shared_ptr<User> BankSystem::getUser(const std::string& userName){
    auto itCustomer = m_customerDatabase.find(userName);
    if(itCustomer != m_customerDatabase.end()){
        return itCustomer->second;
    }
    auto itTeller = m_tellerDatabase.find(userName);
    if(itTeller != m_tellerDatabase.end()){
        return itTeller->second;
    }
    if(m_manger &&m_manger->getuserName() == userName ){
        return m_manger;
    }
    return nullptr;
}

void BankSystem::addCustomerAccount(){
    std::string userName,password;
    std::cout << "Please enter a userName and a password\nuserName:";
    std::cin >> userName;
    std::cout << "\npassword:";
    std::cin >> password;
    system("cls");
    if(searchCustomer(userName)){
        std::cout << "UserName already exist, please pick another one.\n\n";
    }else{
        registerCostumer(userName,password);
        std::cout << "Customer bank account opened successfully.\n\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
}

void BankSystem::addTellerAccount() {
    std::string userName,password;
    std::cout << "Please enter a userName and a password\nuserName:";
    std::cin >> userName;
    std::cout << "\npassword:";
    std::cin >> password;
    system("cls");
    if(searchTeller(userName)){
        std::cout << "UserName already exist, please pick another one.\n\n";
    }else{
        registerTeller(userName,password);
        std::cout << "Teller account opened successfully.\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
}

void BankSystem::replaceManger(){
    std::string userName,password;
    std::cout << "Please enter a userName and a password\nuserName:";
    std::cin >> userName;
    std::cout << "\npassword:";
    std::cin >> password;
    system("cls");
    if(m_manger){
        std::cout << m_manger->getuserName() << "was replaces, new manger account opened successfully.\n";
    }else{
        std::cout << "Manger account opened successfully.\n";
    }
    registerManger(userName,password);
    std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
}













