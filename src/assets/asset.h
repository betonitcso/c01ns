#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>
#include <unistd.h>


#include "../utils/crypto_utils.h"
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
void strToLower(string& s);

class Asset {
    protected:
        string last_updated;

        string id;
        string symbol;
        string name;
        string created_at;

        string description;
        string github;
        string homepage;

        long double current_price;
        long double market_cap;
        long double ath;
        double price_change_percentage[7];
        double price_change_usd[7];
        double market_cap_change_percentage_24h;

        double sentiment[2];
        double developer_score;
        double community_score;
        double liquidity_score;

        unsigned int market_cap_rank;
        
        // Attributes for trading on Alpaca
        long double trade_size;
        bool tradable;
        bool marginable;
        bool shortable;
        bool easyToBorrow;
        bool fractionable;
    public:
        Asset(string asset);
        void info(bool verbose = false);
        void get(bool live = false); // get data without alpaca
};



#endif