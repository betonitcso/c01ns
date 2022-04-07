#include "./client.h"

Client::~Client() {
    curl_easy_cleanup(curl);
}

Client::Client(string public_key, string private_key) {

        
        curl = curl_easy_init();
        if(!curl) {
            std::cerr << "[ERR] Can't initalize libcurl."<< std::endl;
        }
        if(!connectAccount(public_key, private_key)) {
            std::cerr << "[ERR] Invalid credentials." << std::endl;
        } else {
            std::cout << "[INFO] Successfully connected to your Alpaca account." << std::endl;
            std::cout << "[INFO] Account ID: "  << ACCT_ID << std::endl;
            std::cout << "[INFO] Portfolio value: $" << PORTFOLIO_VALUE<< std::endl;
        }

        API_KEY = public_key;
        API_SECRET = private_key;
}

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}  // this is from StackOverFlow

bool Client::connectAccount(string public_key, string private_key) {

    json parsedResponse ;
    string usr_status;
    string body;
    string public_header = "APCA-API-KEY-ID:"; 
    string private_header = "APCA-API-SECRET-KEY:";
    curl_slist* authData = NULL; 

    // set API endpoint for account
    curl_easy_setopt(curl, CURLOPT_URL,  "https://api.alpaca.markets/v2/account");    //  URL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);  // callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);  // writes to body

    // format keys
    public_header = public_header + public_key;  // concats API key
    private_header = private_header + private_key;  // concats API secret
    authData = curl_slist_append(authData,  public_header.c_str());
    authData = curl_slist_append(authData, private_header.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, authData); // HTTP header with public & private keys
   
        
    // send request
    curl_easy_perform(curl);
    curl_slist_free_all(authData);

    //handle response
    parsedResponse= json::parse(body);

    usr_status = parsedResponse.value("status", "ERR");
    ACCT_ID = parsedResponse.value("id", "ACCT_ID_ERR");
    ACCT_BLOCKED = parsedResponse.value("account_blocked", false);
    CASH = atol( parsedResponse.value("cash", "0.0").c_str());
    PORTFOLIO_VALUE = atol(parsedResponse.value("portfolio_value", "0.0").c_str());

   if(!strcmp(usr_status.c_str(), "ACTIVE")) {
        return true;
   }    else return false;
}

int main (){
    Client myClient("AKO4KOQJR39A06E1ER3M",  "LjGXMYkih8AhOVGS2iyIoo9PZaCCbbw4zmHYipjV");
}

//compilation: g++ test.cpp  -lpthread -ldl -lcurl -o trader.exe