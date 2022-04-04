#include "./client.h"

Client::Client() {
    curl = curl_easy_init();
        if(!curl) {
            std::cerr << "[ERR] Can't initalize libcurl.\nTo download it, go to https://curl.se/download.html" << std::endl;
     }
}

Client::~Client() {
    curl_easy_cleanup(curl);
}

void Client::auth(string public_key, string private_key) {
        API_KEY = public_key;
        API_SECRET = private_key;
        if(!validateAccount(public_key, private_key)) {
            std::cerr << "[ERR] Invalid credentials." << std::endl;
        }
}

Client::Client(string public_key, string private_key) {
        curl = curl_easy_init();
        if(!curl) {
            std::cerr << "[ERR] Can't initalize libcurl."<< std::endl;
        }
        auth(public_key, private_key);
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool Client::validateAccount(string public_key, string private_key) {

    string body;

    // set API endpoint for account
    string accountEndpoint = "https://api.alpaca.markets/v2/account";  //  API endpoint
    curl_easy_setopt(curl, CURLOPT_URL,  accountEndpoint.c_str());    // sets URL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  // defines callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);  // writes to body


    // set HTTP header with public & private keys
    curl_slist* authData = NULL;  // header list

    string public_header = "APCA-API-KEY-ID:"; 
    public_header = public_header + public_key;  // concats API key
    string private_header = "APCA-API-SECRET-KEY: ";
    private_header = private_header + private_key;  // concats API secret
    authData = curl_slist_append(authData,  public_header.c_str());
    authData = curl_slist_append(authData, private_header.c_str());

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, authData);
        
    // send request
    curl_easy_perform(curl);
    curl_slist_free_all(authData);

    json parsedResponse = json::parse(body);
    string usr_status = parsedResponse.value("status", "ERR");

    std::cout << std::setw(4) << parsedResponse << std::endl;

   if(!strcmp(usr_status.c_str(), "ACTIVE")) {
        return true;
   }
    else return false;
}

int main (){
    Client myClient("AKO4KOQJR39A06E1ER3M",  "LjGXMYkih8AhOVGS2iyIoo9PZaCCbbw4zmHYipjV");
}

//compilation: g++ test.cpp  -lpthread -ldl -lcurl -o trader.exe