#include <iostream>
#include <string>
#include <curl/curl.h>
#include "../utils/json/single_include/nlohmann/json.hpp"

using std::string;
using json = nlohmann::json;

//Alpaca Live Trading API: https://api.alpaca.markets/



class Client {
    protected:
        string API_KEY;
        string API_SECRET;
        string ACCT_ID;
        bool ACCT_BLOCKED;
        long double CASH ;
        long double PORTFOLIO_VALUE;

        CURL* curl;
    public:
        Client(string public_key, string private_key);
        ~Client();

        bool connectAccount(string public_key, string private_key);
};