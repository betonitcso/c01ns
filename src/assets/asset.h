#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>

#include "../utils/libcurl_utils.h"
#include "../utils/json/single_include/nlohmann/json.hpp"


using std::string;
using json = nlohmann::json;
using LibcurlUtils::alpacaAuthHeaders;

class Asset {
    protected:
        string id;
        string symbol;
        string assetClass;
        string exchange;
        string status;
        string timeStamp; // RFC-3339 timestamp
        long double price;
        long double tradeSize;
        bool tradable;
        bool marginable;
        bool shortable;
        bool easyToBorrow;
        bool fractionable;
    public:
        Asset(string symbol);
        void get(string public_header, string private_header) ;
};



#endif