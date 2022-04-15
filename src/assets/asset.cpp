#include "./asset.h"

string assetServiceAdapter(Service service) {
    CURL* curl = curl_easy_init();

    return "";
};

void Asset::info() {
    CURL* curl = curl_easy_init();
    json parsedResponse;
    string body;
    string tokenURL = "https://api.coingecko.com/api/v3/coins/";
    tokenURL += symbol;

    curl_easy_setopt(curl, CURLOPT_URL, tokenURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlUtils :: writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

    std::cout << "Searching for " << tokenURL << std::endl;


    curl_easy_perform(curl);

    parsedResponse = json :: parse (body);

    curl_easy_cleanup(curl);
};

bool get(string public_key, string private_key, Service service = CoinGecko) {

    CURL* curl = curl_easy_init();
    json parsedResponse ;
    string body;
    curl_slist* headers = AlpacaAuthHeaders(public_key, private_key);
    auto token_endpoint = "https://data.alpaca.markets/v1beta1/crypto/quotes/latest";

    // set API endpoint for account
    curl_easy_setopt(curl, CURLOPT_URL,  token_endpoint);    //  URL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlUtils::writeCallback);  // callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);  // writes to body
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // HTTP header with public & private keys
   
    
    // send request
    curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    //handle response
    parsedResponse= json::parse(body);

    return true;
}

int main() {
   Asset btc("bitcoin");
   btc.info();
}