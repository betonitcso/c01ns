#ifndef CLIENT_H
#define CLIENT_H

#include  <string>
#include <iostream>
#include <vector>

using std::string;

class Asset {
    private:
        string SYMBOL;
        string NAME;
        long double PRICE;
        long double* VOLUME; 
        bool IS_SHORTABLE;
    public:
        Asset();
};

class Data {
    private:
        int start_time;
        int end_time;
        int intervals; //intervals in UNIX time
        std::vector<long double> payload;
    public:
        Data();
};

class Plotter {
};

class Client {
    private:
        string APC_PUBLIC; // Alpaca API public key
        string APC_PRIVATE; // Alpaca API private key
        bool ACCT_BLOCKED;
        bool CRYPTO_ENABLED;
        long int ACTIVE_TRADES;
        long double ACCT_BALANCE;

        bool live; // live or paper trading
        bool strategy_enabled; // can execute strategies
        
    public:
        Client();
        Client(string public_key, string private_key, bool live_trading = true, bool strategy = true);
        void userInfo();
        bool clientAuth();
        bool sendOrder();
        bool executeStrategy();
};

#endif