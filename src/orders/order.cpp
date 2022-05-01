#include "./order.h"

Order :: Order(string a) {
    this->asset = new Asset(a);
}

Order :: Order(Asset* a) {
    this->asset = a;
}

Asset* Order :: getAsset() {
    return asset;
}

LiveOrder :: LiveOrder(string a ) : Order :: Order(new LiveAsset(a)){
    if(!this->asset->isAlpacaSupported()) {
        std :: cerr << "[ERROR] currency not supported by alpaca." << std :: endl;
    }
    this->query = json();
}

json LiveOrder :: getQuery() {
    return query;
}

json& LiveOrder :: operator[] (string param) {
    return query[param];
}

// usage:

int main() {
    std :: cout << "Orders working. C01NS 0.1.5" << std :: endl;
    LiveOrder order("btc");
    order.getAsset()->info();
    order["notional"] = 5.0;
    order["time_in_force"] = "ioc";
    order["type"] = "market";
    std :: cout << order.getQuery() << std :: endl;
}