#ifndef ORDER_H
#define ORDER_H

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


class Order {
protected:
    Status status;
    int open_timestamp;
    int close_timestamp;
    std::vector<Asset> assets;
    long double amount;
    long double price;
public:

    Status getStatus();
    virtual bool execute( ... );
    int getOpenTimeStamp();
    int getCloseTimestamp();
    long double getAmount();
    long double getPrice();
    long double getPerformance();
    void info();
};

class LiveOrder : public Order {
    string user; // API key of user that made contract
public:
    LiveOrder(string public_key, string private_key) : Order() {};
    bool execute();
    bool cancel();
    bool close();
};

#endif