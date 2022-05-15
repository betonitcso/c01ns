#include "./user.h"
#include "../utils/jporta/Test/memtrace.h"

User :: User(string public_key, string private_key) {

    userData["public_key"] = public_key;
    userData["private_key"] = private_key;

    if(!auth()) {
        std :: cerr << "[ERR] Unable to authenticate user." << std :: endl;
        exit(1);
    }
}

void User :: info() {
    std :: cout << "--------------------------------------------------------------" << std :: endl
    << "User: " << userData["account_number"] << std :: endl
    << "Buying power: " << userData["buying_power"] << std :: endl
    << "Cash: " << userData["cash"] << std :: endl
    << "Equity: " << userData["equity"] << std :: endl
    << "--------------------------------------------------------------" << std :: endl;
}

bool User :: auth() {

    Client client;
    curl_slist* headers = CryptoUtils::AlpacaAuthHeaders(userData["public_key"], userData["private_key"]);

    auto response = client.get("https://api.alpaca.markets/v2/account", headers);

    if(response.getHTTPCode() != 200) {
        return false;
    } else {
        userData.update(response.getResponse(), true); // TODO: decide whether or not you need to merge
        return true;
    }
}

void User :: execute(LiveOrder* order) {
    Client client;
    curl_slist* headers = CryptoUtils::AlpacaAuthHeaders(userData["public_key"], userData["private_key"]);

    ojson query = order->getQuery();
    string orderSymbol = strtoupper((*order)["symbol"]) + "USD";
    query["symbol"] = orderSymbol;

    std :: cout << "[INFO] Order " << query << " sent." << std :: endl;

    auto res = client.post("https://api.alpaca.markets/v2/orders", query, headers);

    if(res.getHTTPCode() != 200) {
        std :: cerr << "[ERR] An error occurred while processing order." << std :: endl;
        std :: cerr << std :: setw(4) << res.getResponse() << std :: endl;
        exit(1);
    } else {
        auto response = res.getResponse();
        std :: cout << "[INFO] Order successfully executed." << std :: endl;
        std :: cout << "Order filled for " << response["symbol"] << " @ " << response["created_at"] << std :: endl;
    }

    
}

json User :: getUserData() {
    json ret = userData;
    ret.erase("private_key");
    return ret;
}

json& User :: operator[] (string data) {
    if(data == "private_key") {
        throw std::invalid_argument("[ERR] Private key is not accessible after assignment.");
    }
    return userData[data];
}

LiveAsset* User :: getAsset(string asset) {
    LiveAsset* a = new LiveAsset(asset);
    return a;
}


/*
int main() {
    auto user = new User("AKRMS5NYNQNY8KES77J8", "7RlH4up0x4LMn2CkEFRX2S5PEb8sl6kHt5vrF4O4");
    LiveOrder* myOrder = new LiveOrder("btc");
    myOrder->getAsset()->info();
    (*myOrder)["notional"] = 5.0;
    (*myOrder)["side"] = "buy";
    (*myOrder)["type"] = "market";
    (*myOrder)["time_in_force"] = "ioc";

    user->execute(myOrder);
}
*/