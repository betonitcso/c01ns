#ifndef JPORTA_FRIENDLY
#define JPORTA_FRIENDLY

#include <string>
#include <iostream>


#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../utils/jporta/Test/memtrace.h"
#include "../utils/jporta/Test/gtest_lite.h"


using std :: string;
using nlohmann :: json;
using ojson = nlohmann :: ordered_json;

class Asset;
class Order;
class User;

class Asset {
    protected:
        json assetData;
    public:
        Asset(string asset);
        virtual void info(bool verbose = false);
        virtual json& operator[](string data);
        virtual void get();
};

class User {
protected:
    std :: vector<Order*> orders;
public:
    User(string public_key, string private_key); // assigns it to data

    bool auth();

    virtual void info();
    virtual json getUserData();

    virtual Asset* getAsset(string asset);
    virtual void execute(Order* order);
    virtual json& operator[]  (string data);
};

class Order {
protected:
    string account;
    json data;
    ojson query;
    User* user;
public:
    Order(Asset* asset);
    virtual ojson getQuery();
    virtual void info();
    ojson& operator[](string param);
};

#endif