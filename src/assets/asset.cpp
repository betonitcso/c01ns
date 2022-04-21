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
    Client client;
    json response = client.get("https://api.coingecko.com/api/v3/coins/list").getResponse();

    for(unsigned int i = 0; i < response.size(); i++) {
        string id = response[i].value("id", "");
        string symbol = response[i].value("symbol", "");
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

void Asset::get() {
    Client client;
    string tokenURL = "https://api.coingecko.com/api/v3/coins/";
    tokenURL += id + "?localization=false&tickers=false&sparkline=false";

    std::cout << "Searching for " << id << " @ https://api.coingecko.com/api/v3/coins/" << std::endl;
    json response = client.get(tokenURL).getResponse();
    json marketData = response.value("market_data", json());

    // fill up object with asset data
    name = response.value("name", "N/A");
    created_at = response.value("genesis-date", "N/A");
    description = response.value("description", json()).value("en", "N/A");
    github = response.value("links", json()).value("repos_url", json()).value("github", json())[0];
    homepage = response.value("links", json()).value("homepage", json())[0];
    current_price = marketData.value("current_price", json()).value("usd", -1.0);
    market_cap = marketData.value("market_cap", json()).value("usd", -1.0);
    ath = marketData.value("ath", json()).value("usd", -1.0);

    price_change_percentage[0] = marketData.value("price_change_percentage_24h", -1.0); // 1 day
    price_change_percentage[1] = marketData.value("price_change_percentage_7d", -1.0); // 1 week
    price_change_percentage[2] = marketData.value("price_change_percentage_14d", -1.0); // 2 weeks
    price_change_percentage[3] = marketData.value("price_change_percentage_30d", -1.0); // 1 mo.
    price_change_percentage[4] = marketData.value("price_change_percentage_60d", -1.0); // 2 months
    price_change_percentage[5] = marketData.value("price_change_percentage_200d", -1.0); // 200 days
    price_change_percentage[6] = marketData.value("price_change_percentage_1y", -1.0); // 1 year

    price_change_usd[0] = marketData.value("price_change_percentage_24h_in_currency", json()).value("usd", -1.0); // 1 day
    price_change_usd[1] = marketData.value("price_change_percentage_7d_in_currency", json()).value("usd", -1.0); // 1 week
    price_change_usd[2] = marketData.value("price_change_percentage_14d_in_currency", json()).value("usd", -1.0); // 2 weeks
    price_change_usd[3] = marketData.value("price_change_percentage_30d_in_currency", json()).value("usd", -1.0); // 1 mo.
    price_change_usd[4] = marketData.value("price_change_percentage_60d_in_currency", json()).value("usd", -1.0); // 2 months
    price_change_usd[5] = marketData.value("price_change_percentage_200d_in_currency", json()).value("usd", -1.0); // 200 days
    price_change_usd[6] = marketData.value("price_change_percentage_1y_in_currency", json()).value("usd", -1.0); // 1 year

    market_cap_change_percentage_24h = marketData.value("market_cap_change_percentage_24h", json());
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


LiveAsset :: LiveAsset(string asset, string public_key, string private_key) {
    Client client;
    string tokenURL = "https://api.alpaca.markets/v2/assets/" + this->symbol;

    this->get();
    client.alpacaAuth(public_key, private_key);
    curl_slist* auth_headers = CryptoUtils :: AlpacaAuthHeaders(client.getPublicKey(), client.getPrivateKey());

    std::cout << "Searching for " << strtoupper(symbol) << " @ https://api.alpaca.markets/v2/assets" << std::endl;
    try {
        json response = client.get(tokenURL, "", auth_headers).getResponse();
        is_tradable = response.value("tradable", false);
        is_marginable = response.value("marginable", false);
        is_shortable = response.value("shortable", false);
        is_easy_to_borrow = response.value("easy_to_borrow", false);
        is_fractionable = response.value("fractionable", false);
        is_alpaca_supported = true;
    }
    catch( ... ) {
        is_alpaca_supported = false;
    }
    
}