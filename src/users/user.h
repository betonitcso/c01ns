#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <string>
#include <vector>


#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../orders/order.h"

using std::string;
using nlohmann::json;

class LiveUser {

    string public_key;
    string private_key;
    bool acct_blocked;
    int created_at;

    long double cash;
    long double portfolio_value;
    long double equity;
    long double initial_margin;
    long double buying_power;

    std::vector<Contract*> contracts;

public:
    LiveUser(string public_key, string private_key);
    bool make(Contract contract);
    bool cancel(Contract contract);

    std::vector<Contract*> getActiveContracts();

};

#endif