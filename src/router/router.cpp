#include "./router.h"
#include "../utils/jporta/Test/memtrace.h"

// METHODS OF OPTION CLASS

void Option :: setRouter(Router* r) {
    router = r;
}

void Option :: setActive() {
    active = true;
}

Option :: operator bool() const {
    if(this == NULL) {
        return false;
    }
    if(router->getArg(key) != "") {
        return true;
    } else return false;
}

void Option :: operator() (){
    std :: cout << "YOU HAVEN'T IMPLEMENTED OPERATOR()" << std :: endl;
}

string Option :: getKey() {
    return this->key;
}

bool Option :: isActive() {
    return active;
}

InputOption* Mode :: getInputOpt(string opt){
    for(Option* storedOpt : options) {
        if(opt == storedOpt->getKey()) {
            if(storedOpt->isActive()) {
                return (InputOption*) storedOpt;
            } else return NULL;
        }
    }
    return NULL;
}

string InputOption :: getValue() {
    if(! this->active) {
        std :: cerr << "[ERR] InputOption is not active, but you've tried to get its value." << std :: endl;
        exit(1);
    }
    return router->getArgValue(this->key);
}

void InputOption :: setValue(string val) {
    value = val;
}

// METHODS OF MODE CLASS

Mode :: Mode(Router& r) :router(r.getRouter()) { }

Mode :: Mode(Router* r) : router(r->getRouter()) {} 

Option* Mode :: getOpt(string opt) {
    for(auto storedOpt : options) {
        if(opt == storedOpt->getKey()) {
            if(storedOpt->isActive()) {
                return storedOpt;
            } else return NULL;
        }
    }
    return NULL;
}

void Mode :: option(Option* opt) {
    for(auto storedOpt : options) {
        if(opt->getKey() == storedOpt->getKey()) {
            std :: cerr << "[ERROR] Two options can't have the same keys within a mode." << std :: endl;
            exit(1);
        }
    }
    options.push_back(opt);
}

void Mode :: run() {
    for(auto opt : options) {
        opt->setRouter(&router);
        if(*opt) {
            opt->setActive();
        }
    }
}

// METHODS OF ROUTER CLASS

Router :: Router(int argc, char** argv) : argc(argc), argv(argv) {
    std :: cout << "Running C01NS version 0.1" << std :: endl;
}

Router& Router :: getRouter() {
    return *this;
}

string Router :: getArg(string arg, unsigned int atIndex) {
    if(atIndex) {
        if(argc < atIndex -1) {
            std :: cerr << "[ERROR] Index error." << std :: endl;
            exit(1);
        }
        return argv[atIndex];
    }
    for(int i = 1; i < argc; i++) {
        if(arg == argv[i]) {
            return argv[i];
        }
    }
    return "";
}

string Router :: getArgValue(string arg, unsigned int atIndex) {
    if(atIndex) {
        if(argc < atIndex -2) {
            std :: cerr << "[ERROR] Index error." << std :: endl;
            exit(1);
        }
        return argv[atIndex+1];
    }
    for(int i = 1; i < argc; i++) {
        if(arg == argv[i]) {
            return argv[i+1];
        }
    }
    return "";
} 

void Router :: switchRoute() {
    auto r = routes.find(this->getArg("", 1));
    if(r != routes.end()) {
        this->mode = r->second;
    } else {
        std :: cerr << "[ERROR] Route not found." << std :: endl;
        exit(1);
    }
}

void Router :: switchRoute(string opt) {
    auto r = routes.find(opt);
    if(r != routes.end()) {
        this->mode = r->second;
    } else {
        std :: cerr << "[ERROR] Route not found." << std :: endl;
        exit(1);
    }
}

void Router :: route(string opt, Mode* mode) {
    routes.insert({opt, mode});
}

void Router :: run() {
    CLIUtils::printInitMessage();
    if(argc < 2) {
        std :: cerr << "First argument not found." << std :: endl;
        exit(1);
    } else {
        this->switchRoute();
    }    
    mode->run();
}

// METHODS OF DATA LASS

void Data :: run() {

    Mode :: run();

    if(*getOpt("account")) {
        std :: cout << "got account" << std :: endl;
        if(*getInputOpt("--auth")) {
            string public_key = getInputOpt("--auth")->getValue();
            string private_key = router.getArgValue(public_key);
            auto user = new User(public_key, private_key);
            user->info();
            delete user;
        } else {
            std :: cerr  << "[ERR] You have to authenticate yourself to use this feature." << std :: endl;
            exit(1);
        }
    }

    else if(*getInputOpt("asset")) {
        try {
            if(*getInputOpt("--auth")) {
                string assetName = getInputOpt("asset")->getValue();
                string public_key = getInputOpt("--auth")->getValue();
                string private_key = router.getArgValue(public_key);
                auto asset = new LiveAsset(assetName, public_key, private_key);
                asset->info();
                delete asset;
            } else {
                string assetName = getInputOpt("asset")->getValue();
                Asset* asset = new Asset(assetName);
                asset->info();
                delete asset;
            }
        }
        catch (std::exception e) {
            std :: cerr << "[ERR] Failed to fetch data." << std :: endl;
            std :: cerr << e.what() << std :: endl;
            exit(1);
        }
            
    }
}

// METHODS OF INSTANT CLASS

void Instant :: run() {
    Mode :: run();

    if(*getInputOpt("buy")) {
        if(*getInputOpt("--auth")) {

            string asset = this->getInputOpt("buy")->getValue();
            string public_key = getInputOpt("--auth")->getValue();
            string private_key = router.getArgValue(public_key);
            
            std :: cout << "[INFO] Buy order for  " << asset << " received." << std :: endl;

            auto user = new User(public_key, private_key);
            auto order = new LiveOrder(asset);
            (*order)["side"] = "buy";
            if(*getInputOpt("-n")) {
                (*order)["notional"] = getInputOpt("-n")->getValue();
                (*order)["type"] = "market";
                (*order)["time_in_force"] = "ioc";
                user->execute(order);
            }
            
            else if(*getInputOpt("-q")) {
                (*order)["qty"] = getInputOpt("-q")->getValue();
                (*order)["type"] = "market";
                (*order)["time_in_force"] = "ioc";
                user->execute(order);
            }
            else {
                throw "[ERR] Buy command operates with the -q or -n flags.";
            }

            delete user;
            delete order;
        }
        else {
            throw "[ERR] Authentication failed.";
        }
    } 
    
    else if(*(this->getInputOpt("sell"))) {
        std :: cout << "[INFO] Sell order for  " << this->getInputOpt("sell")->getValue() << " received."  << std :: endl;
        if(*getInputOpt("--auth")) {

            string asset = this->getInputOpt("sell")->getValue();
            string public_key = getInputOpt("--auth")->getValue();
            string private_key = router.getArgValue(public_key);

            auto user = new User(public_key, private_key);
            auto order = new LiveOrder(asset);
            (*order)["side"] = "sell";
            if(*getInputOpt("-n")) {
                (*order)["notional"] = getInputOpt("-n")->getValue();
                (*order)["type"] = "market";
                (*order)["time_in_force"] = "ioc";
                user->execute(order);
            }
            
            else if(*getInputOpt("-q")) {
                (*order)["qty"] = getInputOpt("-q")->getValue();
                (*order)["type"] = "market";
                (*order)["time_in_force"] = "ioc";
                user->execute(order);
            }
            else {
                throw "[ERR] Sell command operates with the -q or -n flags.";
            }

            delete user;
            delete order;

        }
        else {
            throw "[ERR] Authentication failed.";
        }
    } 
    
    else {
        std :: cerr << "[ERROR] Bad input. Please choose either buy or sell options when using the instant interface." << std :: endl;
        exit(1);
    }

    for(auto opt : options) {
        if(opt != NULL) {
            delete opt;
        }
    }
}


// MAIN FUNC

int main(int argc, char** argv) {
    Router* router = new Router(argc, argv);
    Instant* mode = new Instant(router);
    Data* data = new Data(router);

    Option* acct = new Option("account");
    InputOption* assetData = new InputOption("asset");

    InputOption* auth = new InputOption("--auth");
    InputOption* buy = new InputOption("buy");
    InputOption* sell = new InputOption("sell");

    InputOption* assetIndex = new InputOption("-i");
    InputOption* orderQuantity = new InputOption("-q");
    InputOption* orderNotional = new InputOption("-n");
    InputOption* orderType = new InputOption("--type");

    Option* sellAll = new Option("-a");
    Option* sellPortfolio = new Option ("--portfolio");
    InputOption* sellPercentage = new InputOption("-p");

    mode->option(buy);
    mode->option(sell);
    mode->option(assetIndex);
    mode->option(orderQuantity);
    mode->option(orderNotional);
    mode->option(orderType);
    mode->option(sellAll);
    mode->option(sellPortfolio);
    mode->option(sellPercentage);
    mode->option(auth);

    data->option(acct);
    data->option(assetData);
    data->option(auth);

    router->route("instant", mode);
    router->route("data", data);
    router->run();

    

    delete router;
    
}