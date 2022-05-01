#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>
#include <curl/curl.h>

#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../assets/asset.h"
// #include "../user/user.h"

class User; // to make it work until User is inaccessible


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
    Asset* getAsset();
    /*
    virtual bool execute();
    virtual void info();
    */
};

class LiveOrder : public Order {
protected:
    string account; // API key of user that made order
    json data;
    json query;
    User* user;
public:
    LiveOrder(Asset* asset);
    LiveOrder(string asset);
    virtual json getQuery();
    virtual void info();
    /*
    virtual bool execute(User& user);
    virtual bool execute();
    virtual bool cancel();
    virtual bool close();
    */
    json& operator[](string param);
};

#endif