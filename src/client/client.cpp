#include "./client.h"

Response :: Response (CURL* curl, string body) {
    curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_code);
    response = json :: parse(body);
}

Response& Response :: operator=(const Response& res) {
    http_code = res.http_code;
    response = res.response;
    return *this;
}

long int Response :: getHTTPCode() {
    return http_code;
}

json Response :: getResponse() {
    return response;
}

Response Client :: get(string URL, string query, curl_slist* headers) {
    string body;
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlUtils::writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    if(headers) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }
    curl_easy_perform(curl);
    Response req(curl, body);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    return req;
}

void Client :: alpacaAuth(string public_key, string private_key) {
    curl_slist* auth_headers = NULL;
    auth_headers = CryptoUtils :: AlpacaAuthHeaders(public_key, private_key);

    Response account = this->get("https://api.alpaca.markets/v2/account", "", auth_headers);
    if(account.getHTTPCode() == 200) {
        APCA_PUBLIC_KEY = public_key;
        APCA_PRIVATE_KEY = private_key;
    } else if (account.getHTTPCode() >= 400) {
        std::cout << "[ERROR] Invalid credentials." << std::endl;
        exit(1);
    }
}

string Client :: getPublicKey() {
    return APCA_PUBLIC_KEY;
}

string Client :: getPrivateKey() {
    return APCA_PRIVATE_KEY;
}