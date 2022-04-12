#ifndef WRITECALLBACK_H
#define WRITECALLBACK_H

#include <string>
#include <curl/curl.h>

using std::string;

namespace LibcurlUtils {
     size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }  // this is from StackOverFlow

    curl_slist* alpacaAuthHeaders(string public_key, string private_key) {
        curl_slist* auth = nullptr;
        string alpaca_public = "APCA-API-KEY-ID:";
        string alpaca_private = "APCA-API-SECRET-KEY:";

        alpaca_public = alpaca_public + public_key;
        alpaca_private = alpaca_private + private_key;
        curl_slist_append(auth, alpaca_public.c_str());
        curl_slist_append(auth, alpaca_private.c_str());
        curl_slist_append(auth, "exchange:FTX");
        return auth;
    }
}



#endif