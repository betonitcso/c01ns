#include "./app.h"
#include "../utils/jporta/Test/gtest_lite.h"
#include "../utils/jporta/Test/memtrace.h"

Asset :: Asset(string asset) {
    assetData["symbol"] = asset;
    assetData["name"] = asset;
    assetData["price"] = 30097.000;
    assetData["market_cap"] = 573070921282.000;
    assetData["price_change_24h"] = 1.77307;
    assetData["ath"] = 69045.000;
}

void Asset :: info(bool verbose) {
    std::cout << "[INFO] $" << assetData["symbol"] << std::endl
    << "--------------" << std::endl
    << "Name: " << assetData["name"] << std::endl;
    if(verbose) {
        std::cout << "Description: please use the real app." << std::endl;
    }
    std::cout << "Price: $" << std::fixed  << std::setprecision(3) << assetData["price"] << std::endl
    << "Market cap: $" <<  assetData["market_cap"] <<std::endl
    << "24h price change: " << assetData["price_change_24h"] << "%" << std::endl
    << "ATH: $" << assetData["ath"] << std::endl
    << "--------------" << std::endl
    <<"Github: " <<  "please use the real app." << std::endl
    << "Homepage: " << "please use the real app." << std::endl
    << "--------------" << std::endl;
}

void Asset :: get() {
    return;
}


json& Asset ::  operator[](string data) {
    return this->assetData[data];
}

int main() {
    std :: cout << "Jporta friendly version is working." << std :: endl;
    std :: cout << "Warning: this is not a legit crypto trading app." << std :: endl
    << "Check https://github.com/betonitcso/c01ns for the proper implementation." << std :: endl;
}

