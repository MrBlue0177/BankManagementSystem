cmake_minimum_required(VERSION 3.26)
project(BankMangementSystem)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

# Path to the OpenSSL include directory
set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL-Win64/include")
set(OPENSSL_LIBRARIES "C:/Program Files/OpenSSL-Win64/lib")

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(BankMangementSystem main.cpp
        BankSystem.cpp
        BankSystem.h
        Customer.cpp
        Customer.h
        Teller.cpp
        Teller.h
        Manger.cpp
        Manger.h
        User.cpp
        User.h)

# Link against the OpenSSL libraries using imported targets
target_link_libraries(BankMangementSystem PRIVATE OpenSSL::SSL OpenSSL::Crypto)