#include "./asset.h"

string& strtolower(string& str) {
    for(int i = 0; i < str.length(); i++) {
        str[i] = (char) tolower(str[i]);
    }
    return str;
}

string strtoupper(string str) {
    string ret;
    ret = str;
    for(int i = 0; i < ret.length(); i++) {
        ret[i] = (char) toupper(ret[i]);
    }
    return ret;
}

string assetNameAdapter(string asset, Service service = CoinGecko) {
    asset = strtolower(asset);
    CURL* curl = curl_easy_init();
    string CGEndpoint = "https://api.coingecko.com/api/v3/coins/list";
    string response;
    json parsedResponse;

    curl_easy_setopt(curl, CURLOPT_URL, CGEndpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlUtils :: writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curl);

    parsedResponse = json::parse(response);

    for(unsigned int i = 0; i < parsedResponse.size(); i++) {
        string id = parsedResponse[i].value("id", "");
        string symbol = parsedResponse[i].value("symbol", "");
        if(id== asset || symbol== asset) {
            if(service == Alpaca) return symbol;
            else return id;
        }
    }
    return "";
};

Asset::Asset(string asset) {
    id = assetNameAdapter(asset, CoinGecko);
    symbol = assetNameAdapter(asset, Alpaca);
    name = "";
}

void Asset::get(bool live) {
    CURL* curl = curl_easy_init();
    json parsedResponse;
    string response;
    string tokenURL = "https://api.coingecko.com/api/v3/coins/";
    tokenURL += id + "?localization=false&tickers=false&sparkline=false";

    curl_easy_setopt(curl, CURLOPT_URL, tokenURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, LibcurlUtils :: writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    std::cout << "Searching for " << id << " @ https://api.coingecko.com/api/v3/coins/" << std::endl;
    curl_easy_perform(curl);

    parsedResponse = json::parse(response);

    // fill up object with asset data
    name = parsedResponse.value("name", "N/A");
    created_at = parsedResponse.value("genesis-date", "N/A");
    description = parsedResponse.value("description", json()).value("en", "N/A");
    github = parsedResponse.value("links", json()).value("repos_url", json()).value("github", json())[0];
    homepage = parsedResponse.value("links", json()).value("homepage", json())[0];

    json marketData = parsedResponse.value("market_data", json());

    current_price = marketData.value("current_price", json()).value("usd", -1.0);
    market_cap = marketData.value("market_cap", json()).value("usd", -1.0);
    ath = marketData.value("ath", json()).value("usd", -1.0);

    // price change percentage
    price_change_percentage[0] = marketData.value("price_change_percentage_24h", -1.0); // 1 day
    price_change_percentage[1] = marketData.value("price_change_percentage_7d", -1.0); // 1 week
    price_change_percentage[2] = marketData.value("price_change_percentage_14d", -1.0); // 2 weeks
    price_change_percentage[3] = marketData.value("price_change_percentage_30d", -1.0); // 1 mo.
    price_change_percentage[4] = marketData.value("price_change_percentage_60d", -1.0); // 2 months
    price_change_percentage[5] = marketData.value("price_change_percentage_200d", -1.0); // 200 days
    price_change_percentage[6] = marketData.value("price_change_percentage_1y", -1.0); // 1 year

    //price change in USD
    price_change_usd[0] = marketData.value("price_change_percentage_24h_in_currency", json()).value("usd", -1.0); // 1 day
    price_change_usd[1] = marketData.value("price_change_percentage_7d_in_currency", json()).value("usd", -1.0); // 1 week
    price_change_usd[2] = marketData.value("price_change_percentage_14d_in_currency", json()).value("usd", -1.0); // 2 weeks
    price_change_usd[3] = marketData.value("price_change_percentage_30d_in_currency", json()).value("usd", -1.0); // 1 mo.
    price_change_usd[4] = marketData.value("price_change_percentage_60d_in_currency", json()).value("usd", -1.0); // 2 months
    price_change_usd[5] = marketData.value("price_change_percentage_200d_in_currency", json()).value("usd", -1.0); // 200 days
    price_change_usd[6] = marketData.value("price_change_percentage_1y_in_currency", json()).value("usd", -1.0); // 1 year

    market_cap_change_percentage_24h = marketData.value("market_cap_change_percentage_24h", json());

    curl_easy_cleanup(curl);
}


void Asset::info(bool verbose) {
    if(name == "") {
        this->get();
    }
    std::cout << "[INFO] $" << strtoupper(symbol) << std::endl
    << "--------------" << std::endl
    << "Name: " << name << std::endl;
    if(verbose) {
        std::cout << description << std::endl;
    }
    std::cout << "Price: $" << std::fixed  << std::setprecision(3) <<current_price << std::endl
    << "Market cap: $" <<  market_cap <<std::endl
    << "24h price change: " << price_change_percentage[0] << "%" << std::endl
    << "24h market cap change: " <<market_cap_change_percentage_24h << "%" << std::endl
    << "ATH: $" << ath << std::endl
    << "--------------" << std::endl
    <<"Github: " <<  github << std::endl
    << "Homepage: " << homepage << std::endl
    << "--------------" << std::endl;
    
};