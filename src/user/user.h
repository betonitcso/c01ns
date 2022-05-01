#ifndef USER_H
#define USER_H

// STANDARD LIB INCLUDES
#include <string>
#include <iostream>
#include <vector>

// 3RD PARTY INCLUDES
#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../assets/asset.h"
#include "../orders/order.h"

// USING STRING & json
using std :: string;
using nlohmann :: json;

class User {
protected:
    string APCA_PUBLIC_KEY;
    string APCA_PRIVATE_KEY;
    json data;
    std :: vector<LiveOrder*> orders;
public:
    User(string public_key, string private_key);

    bool auth();

    virtual void userInfo();
     virtual json getUserData();

    virtual std :: vector<LiveOrder*> getOrders(bool active = false, bool pending = false, bool closed = false);
    virtual LiveAsset* getAsset(string asset);
    virtual string getPrivateKey();
    virtual string getPublicKey();

    virtual void execute(LiveOrder* order);
    virtual LiveOrder* order(json query);
};


#endif