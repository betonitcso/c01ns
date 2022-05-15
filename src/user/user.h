#ifndef USER_H
#define USER_H

// STANDARD LIB INCLUDES
#include <string>
#include <iostream>
#include <vector>
#include <exception>

// 3RD PARTY INCLUDES
#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../client/client.h"
#include "../assets/asset.h"
#include "../orders/order.h"

// USING STRING & json
using std :: string;
using nlohmann :: json;

class User {
protected:
    json userData; // contains APCA_PUBLIC_KEY & APCA_PRIVATE_KEY
    std :: vector<LiveOrder*> orders;
public:
    User(string public_key, string private_key); // assigns it to data

    bool auth();

    //virtual void info();
    virtual json getUserData();

    // virtual std :: vector<LiveOrder*> getOrders(bool active = false, bool pending = false, bool closed = false);
    virtual LiveAsset* getAsset(string asset);
    // virtual string getPrivateKey();
    // virtual string getPublicKey();

    virtual void execute(LiveOrder* order);
    // virtual LiveOrder* order(json query);
    virtual json& operator[]  (string data);
};


#endif