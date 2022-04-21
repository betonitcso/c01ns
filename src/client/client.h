#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <curl/curl.h>
#include  <iostream>
#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../utils/crypto_utils.h"
#include "../utils/libcurl_utils.h"

using nlohmann:: json;
using std::string;

class Response {
private:
    long int http_code;
    json response;
public:
    Response (CURL* curl, string body) ;
    long int getHTTPCode();
    json getResponse();

    Response& operator=(const Response& res);
};

class Client {
protected:
    CURL* curl;
    string APCA_PUBLIC_KEY;
    string APCA_PRIVATE_KEY;
public:

    void printGarbage();

    Client() {
        curl = curl_easy_init();
    }

    Response get(string URL, string query = "", curl_slist* headers = NULL);
    void alpacaAuth(string public_key, string private_key);
    string getPublicKey();
    string getPrivateKey();
};


#endif