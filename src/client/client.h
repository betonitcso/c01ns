#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <curl/curl.h>
#include  <iostream>
#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../utils/libcurl_utils.h"

using nlohmann:: json;
using ojson = nlohmann :: ordered_json;
using std::string;

class Response {
private:
    long int http_code;
    json response;
public:
    Response (CURL* curl, string body) ;
    long int getHTTPCode();
    json getResponse();
};

class Client {
protected:
    CURL* curl;
public:
    Client() {
        curl = curl_easy_init();
    }
    Response get(string URL, curl_slist* headers = NULL);
    Response post(string URL, json query, curl_slist* headers = NULL);
};


#endif