#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>
#include <curl/curl.h>
#include  <iostream>
#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../utils/libcurl_utils.h"

using nlohmann:: json;
using std::string;

class Request {
private:
    long int http_code;
    json response;
public:
    Request (CURL* curl, string body) ;
    long int getHTTPCode();
    json getResponse();
};

class Client {
protected:
    CURL* curl;
    string APCA_PUBLIC_KEY;
    string APCA_PRIVATE_KEY;
public:

    Client() {
        curl = curl_easy_init();
    }

    Request get(string URL, string query = "", curl_slist* headers = NULL);

    void auth(string public_key, string private_key);
};


#endif