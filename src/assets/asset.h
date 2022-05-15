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

#include "../utils/jporta/Test/memtrace.h"
#include "../utils/jporta/Test/gtest_lite.h"

using std::string;
using json = nlohmann::json;

enum Service {
    CoinGecko,
    Alpaca
};

string assetNameAdapter(Service s);
string& strtolower(string& str);
string strtoupper(string str);

class Asset {
    protected:
        string last_updated; 

        json assetData;

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
        double market_cap_change_percentage_24h;

        double sentiment[2];
        double developer_score;
        double community_score;
        double liquidity_score;

        unsigned int market_cap_rank;


        bool is_alpaca_supported;
    public:
        Asset(string asset);
        virtual void info(bool verbose = false); // if verbose: prints unnecessary stuff too
        virtual json& operator[](string data);
        virtual void get(); // sends req to coingecko, assigns res to coinGeckoData

        string getSymbol() {
            return symbol;
        }
        bool isAlpacaSupported();
};

class LiveAsset : public Asset {
    protected:

        long double trade_size;
        string status;
        bool is_tradable;
        bool is_marginable;
        bool is_shortable;
        bool is_easy_to_borrow;
        bool is_fractionable;

    public:
        LiveAsset(string asset, string public_key, string private_key);
        LiveAsset(string asset);
        bool isAlpacaSupported();
        virtual void info(bool verbose = false);
        virtual json& operator[] (string data);
};



#endif