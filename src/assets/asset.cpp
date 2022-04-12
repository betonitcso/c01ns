#include "./asset.h"

void Asset::get(string public_key, string private_key) {

    CURL* curl = curl_easy_init();
    json parsedResponse ;
    string body;
    curl_slist* headers = alpacaAuthHeaders(public_key, private_key);
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
    std::cout << std::setw(4) << parsedResponse << std::endl;

}

int main() {
   std::cout <<  "Hello World!" << std::endl;
   Asset("BTCUSD");
}