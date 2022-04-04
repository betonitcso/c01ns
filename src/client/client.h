#include <iostream>
#include <string>
#include <curl/curl.h>
#include "../utils/json/single_include/nlohmann/json.hpp"

using std::string;
using json = nlohmann::json;

//Alpaca Live Trading API: https://api.alpaca.markets/



class Client {
    private:
        string API_KEY;
        string API_SECRET;
        CURL* curl;
    public:
        Client(void);
        Client(string public_key, string private_key);
        ~Client();

        void  auth(string public_key, string private_key);
        bool validateAccount(string public_key, string private_key);
};