#include "./order.h"

Order :: Order(string a) {
    this->asset = new Asset(a);
}

LiveOrder :: LiveOrder(string a ) {

}

json& LiveOrder :: operator[] (string param) {
    return query[param];
}

int main() {
    std :: cout << "Orders working. C01NS 0.1.5" << std :: endl;
    LiveOrder order("btc");
    order["notional"] = 5.0;
}