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

Response Client :: get(string URL, curl_slist* headers) {
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


Response Client :: post(string URL, json query, curl_slist* headers) {
    string body;
    // WEIRD BUG: alpaca doesn't accept dumped ordered_json or basic_json, but if you dump->parse->dump->c_str(), it works.
    string newQuery = json :: parse(query.dump()).dump();

    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlUtils::writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, newQuery.c_str());
    if(headers) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }
    curl_easy_perform(curl);
    Response req(curl, body);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    return req;
}

/*

Usage:
int main() {
    json query = {
        {"symbol" , "BTCUSD"},
        {"notional" , 5.0},
        {"side" , "buy"}, 
        {"type" , "market"},
        {"time_in_force" ,"ioc"}
    };

    curl_slist* auth = nullptr;
    auth = curl_slist_append(auth, "your_alpaca_public_key_header");
    auth = curl_slist_append(auth, "your_alpaca_private_key_header");

    Client client;
    Response r = client.post("https://api.alpaca.markets/v2/orders", query, auth);

    std :: cout << std :: setw(4) << r.getResponse() << std :: endl;
}
*/