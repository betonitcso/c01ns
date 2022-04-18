#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <string>
#include <vector>


#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../contracts/contract.h"

using std::string;
using nlohmann::json;

class User {

protected:
    long double ACCT_BALANCE;
    long double ACCT_PORTFOLIO_VALUE;
    Contract* contracts;

public:
    //constructor
    User(long double balance) : ACCT_BALANCE(balance) {};
};


class PaperUser : public User{
public:
    PaperUser(long double balance = 10000.0) : User(balance) {};
    void setBalance(long double amount);
};

class LiveUser : public User {

protected:
    string APC_PUBLIC_KEY;
    string APC_PRIVATE_KEY;

public:
    LiveUser(string public_key, string private_key); // constructor
    virtual bool auth(string public_key, string private_key); // authorizes alpaca account
    virtual void info(); // prints user information
};


#endif