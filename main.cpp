#include <iostream>
#include <chrono>
#include <thread>

#include "BankSystem.h"
#include "User.h"
#include "Customer.h"
#include "Teller.h"
#include "Manger.h"

// ------consts--------
const int PAUSE_TIME= 3;
//---------------------


//Initialize BankSystem:
BankSystem bankSystem;

// ------prints-------
void printInvalidInput(){
    std::cout << std::endl << "Invalid Input, Please Try Again" << std::endl << std::endl;
}
void printLoginSuccessful(const std::string& userName){
    std::cout << userName << " you have successfully logged-in." << std::endl;
}
//---------------------

// -----MainFunctions -----
int mainMenu();
void customerMenu(const std::shared_ptr<Customer>& customer);
void tellerMenu(std::shared_ptr<Teller> teller);
void mangerMenu(std::shared_ptr<Manger> manger);
void login();
void holdPageUntilR();
// -------------------







int main() {
    if(!bankSystem.isThereAManger()){
        std::cout<<"To start a bank management system we need atleast one manger.\nplease open a manger account to be able to continue.\n";
        bankSystem.replaceManger();
    }
    system("cls");
    int choice= mainMenu();
    system("cls");
    switch(choice){
        case 1:
            login();
        case 2:
            bankSystem.addCustomerAccount();
            main();
        case 3:
            break;
        default:
            std::cout << "please select from the options given" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
            main();
    }
    exit(0);
}

int mainMenu(){
    std::cout << "Bank Management System Menu:" << std::endl;
    std::cout << "1. login" << std::endl;
    std::cout << "2. Open a Customer Account" << std::endl;
    std::cout << "3. Exit" << std::endl << std::endl;
    std::cout << "Enter your Choice: " ;
    int choice;
    if(!(std::cin >> choice)){
        return 0;
    }
    std::cout << std::endl << std::endl;
    return choice;
}

void customerMenu(const std::shared_ptr<Customer>& customer){
    system("cls");
    std::cout << "1. Withdraw" << std::endl;
    std::cout << "2. Deposit" << std::endl;
    std::cout << "3. Transaction" << std::endl;
    std::cout <<"4. Change password" << std::endl;
    std::cout << "5. Show Account Details" << std::endl;
    std::cout << "6. logout" << std::endl;
    std::cout << "Enter your choice:";
    int choice;
    if(!(std::cin >> choice)){
        system("cls");
        printInvalidInput();
        std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
        customerMenu(customer);
    }
    system("cls");
    switch(choice){
        case 1:
            customer->withDraw();
            break;
        case 2:
            customer->deposit();
            break;
        case 3:
            customer->transaction(customer);
            break;
        case 4:
            customer->changePassword(customer);
            break;
        case 5: {
            customer->printUserDetails();
            holdPageUntilR();
            break;}
        case 6:
            main();
            break;
        default:
            system("cls");
            printInvalidInput();
            std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
            break;
    }
    customerMenu(customer);
}

void tellerMenu(std::shared_ptr<Teller> teller){
    system("cls");
    std::cout<<"1. open a Customer Account\n";
    std::cout<<"2. delete a Customer Account\n";
    std::cout<<"3. open a Teller Account\n";
    std::cout<<"4. delete a Teller Account\n";
    std::cout<<"5. change password\n";
    std::cout<<"6. change a customer password\n";
    std::cout<<"7. process a transaction\n";
    std::cout<<"8. see a Customer's Account details\n";
    std::cout<<"9. exit\n\n";
    std::cout << "Enter your choice:";
    int choice;
    if(!(std::cin >> choice)){
        system("cls");
        printInvalidInput();
        std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
        tellerMenu(teller);
    }
    system("cls");
    switch(choice){
        case 1:
            bankSystem.addCustomerAccount();
            break;
        case 2:
            bankSystem.deleteCustomer();
            break;
        case 3:
            bankSystem.addTellerAccount();
            break;
        case 4:
            if(bankSystem.deleteTeller(teller->getuserName())){
                std::cout << "You deleted your own account.\n";
                main();
            }
            break;
        case 5:
            teller->changePassword(teller);
            break;
        case 6:
            teller->changeCustomersPassword();
            break;
        case 7:
            teller->proccessTransaction();
            break;
        case 8:
            teller->printCustomerDetails();
            holdPageUntilR();
            break;
        case 9:
            main();
            break;
        default:
            system("cls");
            printInvalidInput();
            std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
            break;
    }
    tellerMenu(teller);
}

void mangerMenu(std::shared_ptr<Manger> manger){
    system("cls");
    std::cout<<"1. open a Teller Account\n";
    std::cout<<"2. delete a Teller Account\n";
    std::cout<<"3. change password\n";
    std::cout<<"4. change a teller's password\n";
    std::cout<<"5. print all customers\n";
    std::cout<<"6. print all tellers\n";
    std::cout<<"7. exit\n\n";
    std::cout << "Enter your choice:";

    int choice;
    if(!(std::cin >> choice)){
        system("cls");
        printInvalidInput();
        std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
        mangerMenu(manger);
    }
    system("cls");
    switch(choice){
        case 1:
            bankSystem.addTellerAccount();
            break;
        case 2:
            bankSystem.deleteTeller("");
            break;
        case 3:
            manger->changePassword(manger);
            break;
        case 4:
            manger->changeTellerPassword();
            break;
        case 5:
            manger->printCustomers();
            holdPageUntilR();
            break;
        case 6:
            manger->printTellers();
            holdPageUntilR();
            break;
        case 7:
            main();
            break;
        default:
            system("cls");
            printInvalidInput();
            std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
            break;
    }
    mangerMenu(manger);
}

void login(){
    std::cout <<"please enter your userName and password\n";
    std::cout << "UserName:";
    std::string userName;
    std::cin >> userName;
    std::cout << std::endl << "password:";
    std::string password;
    if(!(std::cin >> password)) {
        system("cls");
        printInvalidInput();
        main();
    }
    system("cls");

    std::shared_ptr<User> current = bankSystem.authinticate(userName,password);
    std::shared_ptr<Customer> customer = std::dynamic_pointer_cast<Customer>(current);
    std::shared_ptr<Teller> teller = std::dynamic_pointer_cast<Teller>(current);
    std::shared_ptr<Manger> manger = std::dynamic_pointer_cast<Manger>(current);
    if(!current){
        std::cout << "LOGIN ERROR\nwrong userName or password" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
        main();
    }else{
        if(customer){
            printLoginSuccessful(userName);
            std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
            customerMenu(customer);
        }else if(teller){
            printLoginSuccessful(userName);
            std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
            tellerMenu(teller);
        }else if(manger){
            printLoginSuccessful(userName);
            std::this_thread::sleep_for(std::chrono::seconds(PAUSE_TIME));
            mangerMenu(manger);
        }
    }

}


void holdPageUntilR(){
    std::string choice;
    std::cout <<"\nenter 'r' if you which to return\n";
    do{
        std::cin >> choice;
    }while(choice != "r");
}


