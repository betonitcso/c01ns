#include "./order.h"
#include "../utils/jporta/Test/memtrace.h"

Order :: ~Order() {
    return;
}

Order :: Order(string a) {
    this->asset = new Asset(a);
}

Order :: Order(Asset* a) {
    this->asset = a;
}

Asset* Order :: getAsset() {
    return asset;
}

LiveOrder :: ~LiveOrder() {
    delete this->asset;
}

LiveOrder :: LiveOrder(string a ) : Order :: Order(new LiveAsset(a)){
    this->query = json();
    query["symbol"] = (*asset) ["symbol"];
}

void LiveOrder :: info() {
    std :: cout << data << std :: endl;
}

ojson LiveOrder :: getQuery() {
    return query;
}

ojson& LiveOrder :: operator[] (string param) {
    return query[param];
}



/*
int main() {
    std :: cout << "Orders working. C01NS 0.1.5" << std :: endl;
    LiveOrder order("btc");
    order.getAsset()->info();
    order["notional"] = 5.0;
    order["side"] = "buy";
    order["type"] = "market";
    order["time_in_force"] = "ioc";
    std :: cout << order.getQuery() << std :: endl;
}
*/