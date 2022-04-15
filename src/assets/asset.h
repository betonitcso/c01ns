#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>

#include "../utils/alpaca_utils.h"
#include "../utils/libcurl_utils.h"
#include "../utils/json/single_include/nlohmann/json.hpp"

using std::string;
using json = nlohmann::json;
using AlpacaUtils :: AlpacaAuthHeaders;

enum Service {
    CoinGecko,
    Alpaca
};

string assetNameAdapter(Service s);

class Asset {
    protected:
        string id;
        string symbol;
        string assetClass;
        string last_updated;
        long double price;
        long double tradeSize;
        bool tradable;
        bool marginable;
        bool shortable;
        bool easyToBorrow;
        bool fractionable;
    public:
        Asset(string symbol) :symbol(symbol) { };
        void info();
        bool get(string public_header, string private_header, Service service = CoinGecko) ;
};



#endif