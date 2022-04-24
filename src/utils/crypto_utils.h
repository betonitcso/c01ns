#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <curl/curl.h>
#include <string>
#include <tuple>
#include <vector>

#include "../assets/asset.h"
#include "./json/single_include/nlohmann/json.hpp"

using nlohmann::json;
using std::string;

namespace  CryptoUtils {
    inline curl_slist* AlpacaAuthHeaders(string public_key, string private_key) {
        curl_slist* auth = nullptr;
        string alpaca_public = "APCA-API-KEY-ID:";
        string alpaca_private = "APCA-API-SECRET-KEY:";

        alpaca_public = alpaca_public + public_key;
        alpaca_private = alpaca_private + private_key;
        auth = curl_slist_append(auth, alpaca_public.c_str());
        auth = curl_slist_append(auth, alpaca_private.c_str());
        return auth;
    }
};


#endif