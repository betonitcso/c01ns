#include "./user.h"
#include "../utils/jporta/Test/memtrace.h"

User :: User(string public_key, string private_key) {

    userData["public_key"] = public_key;
    userData["private_key"] = private_key;

    if(!auth()) {
        throw CLIUtils :: AuthError("[ERR] Unable to authenticate user.");
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
        userData.update(response.getResponse(), true);
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
        throw CLIUtils :: QueryError("[ERR] An error occurred while processing order.");
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
        throw CLIUtils :: ForbiddenCommand("[ERR] Private key is not accessible after assignment.");
    }
    return userData[data];
}

LiveAsset* User :: getAsset(string asset) {
    LiveAsset* a = new LiveAsset(asset);
    return a;
}