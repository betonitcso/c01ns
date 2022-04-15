#ifndef ALPACA_UTILS_H
#define ALPACA_UTILS_H

#include <curl/curl.h>
#include <string>
#include <tuple>
#include <vector>

using std::string;
using std::tuple;

namespace AlpacaUtils {
    curl_slist* AlpacaAuthHeaders(string public_key, string private_key) {
        curl_slist* auth = nullptr;
        string alpaca_public = "APCA-API-KEY-ID:";
        string alpaca_private = "APCA-API-SECRET-KEY:";

        alpaca_public = alpaca_public + public_key;
        alpaca_private = alpaca_private + private_key;
        curl_slist_append(auth, alpaca_public.c_str());
        curl_slist_append(auth, alpaca_private.c_str());
        return auth;
    };

};


#endif