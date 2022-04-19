#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <iostream>
#include <vector>
#include <curl/curl.h>

#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../assets/asset.h"

using std::string;

enum Status  {
    pending,
    active,
    cancelled,
    closed
};


class Contract {
protected:
    Status status;
    int open_timestamp;
    int close_timestamp;
    std::vector<Asset> assets;
    long double amount;
    long double price;
public:

    Status getStatus();
    int getOpenTimeStamp();
    int getCloseTimestamp();
    long double getAmount();
    long double getPrice();
    long double getPerformance();
    void info();
};

class LiveContract : public Contract {
    string user; // API key of user that made contract
public:
    LiveContract(string public_key) : Contract() {};
    bool make();
    bool cancel();
    bool close();
};

#endif