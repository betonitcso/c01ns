#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>
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
    Asset* asset;
public:
    Order(string asset);
    Order(Asset* asset);
    virtual bool execute();
    virtual void info();
};

class LiveOrder : public Order {
protected:
    string account; // API key of user that made contract
    json query;
public:
    LiveOrder(Asset* asset) : Order :: Order(asset) {};
    LiveOrder(string asset) : Order :: Order(asset) {};
    virtual bool execute(string public_key, string private_key);
    virtual bool execute();
    virtual bool cancel();
    virtual bool close();

    json& operator[](string param);
};

#endif