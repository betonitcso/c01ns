#include "./client.h"

Request :: Request (CURL* curl, string body) {
    curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_code);
    response = json :: parse(body);
}

long int Request :: getHTTPCode() {
    return http_code;
}

json Request :: getResponse() {
    return response;
}

Request Client :: get(string URL, string query, curl_slist* headers) {
    string body;
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlUtils::writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    if(headers) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }
    curl_easy_perform(curl);
    Request req(curl, body);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    return req;
}

void Client :: auth(string public_key, string private_key) {
    curl_slist* auth_headers = NULL;
    string public_header = "APCA-API-KEY-ID:" + public_key;
    string private_header = "APCA-API-SECRET-KEY:" + private_key;
    auth_headers = curl_slist_append(auth_headers, public_header.c_str());
    auth_headers = curl_slist_append(auth_headers, private_header.c_str());

    Request account = this->get("https://api.alpaca.markets/v2/account", "", auth_headers);
    if(account.getHTTPCode() == 200) {
        APCA_PUBLIC_KEY = public_key;
        APCA_PRIVATE_KEY = private_key;
    } else if (account.getHTTPCode() >= 400) {
        std::cout << "[ERROR] Invalid credentials." << std::endl;
        exit(1);
    }
}