#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>
#include <unistd.h>

#include "../client/client.h"
#include "../utils/crypto_utils.h"
#include "../utils/json/single_include/nlohmann/json.hpp"

using std::string;
using json = nlohmann::json;

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
    public:
        Asset(string asset);
        void info(bool verbose = false); // if verbose: prints a lot of unnecessary stuff too
        void get(); // get data -  if live: get alpaca data too

        string getSymbol() {
            return symbol;
        }
};

class LiveAsset : public Asset {
    protected:
        long double trade_size;
        string status;
        bool is_alpaca_supported;
        bool is_tradable;
        bool is_marginable;
        bool is_shortable;
        bool is_easy_to_borrow;
        bool is_fractionable;

    public:
        LiveAsset(string asset, string public_key, string private_key) : Asset(asset) {};
};



#endif