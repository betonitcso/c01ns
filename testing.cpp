#include <string>
#include <iostream>
#include "./src/utils/crypto_utils.h"

using std::string;

int main() {
    CryptoUtils :: AlpacaOrderQuery btc("BTC") ;
    btc.add("notional", "5.0");
   std::cout << btc.makeQuery() << std::endl;
}