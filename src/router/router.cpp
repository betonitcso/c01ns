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
        throw CLIUtils :: ForbiddenCommand("[ERR] InputOption is not active, but you've tried to get its value." );
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
            throw CLIUtils :: ForbiddenCommand("[ERR] Two options can't have the same keys within a mode." );
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
            throw CLIUtils :: InternalError("[ERR] Index error.");
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
            throw CLIUtils :: InternalError("[ERR] Index error.");
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
        throw CLIUtils :: ForbiddenCommand("[ERR] Route not found." );
    }
}

void Router :: switchRoute(string opt) {
    auto r = routes.find(opt);
    if(r != routes.end()) {
        this->mode = r->second;
    } else {
        throw CLIUtils :: ForbiddenCommand("[ERR] Route not found." );
    }
}

void Router :: route(string opt, Mode* mode) {
    routes.insert({opt, mode});
}

void Router :: run() {
    CLIUtils::printInitMessage();
    if(argc < 2) {
        throw CLIUtils :: ForbiddenCommand("[ERR] First argument not found.");
    } else {
        this->switchRoute();
    }    
    mode->run();
}

// METHODS OF DATA LASS

void Data :: run() {
    Mode :: run();

    if(*getOpt("account")) {
        if(*getInputOpt("--auth")) {
            string public_key = getInputOpt("--auth")->getValue();
            string private_key = router.getArgValue(public_key);
            auto user = new User(public_key, private_key);
            user->info();
            delete user;
        } else {
            throw CLIUtils :: AuthError("[ERR] You have to authenticate yourself to use this feature." );
        }
    }

    else if(*getInputOpt("asset")) {
        if(*getInputOpt("--auth")) {
                string assetName = getInputOpt("asset")->getValue();
                string public_key = getInputOpt("--auth")->getValue();
                string private_key = router.getArgValue(public_key);
                auto asset = new LiveAsset(assetName, public_key, private_key);
                asset->info();
                if(asset != nullptr) {
                    delete asset;
                }
            } else {
                string assetName = getInputOpt("asset")->getValue();
                Asset* asset = new Asset(assetName);
                asset->info();
                if(asset != nullptr) {
                    delete asset;
                }
            }
            
    }
    else {
        throw CLIUtils :: ForbiddenCommand("[ERR] Wrong arguments given.");
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
                throw CLIUtils :: ForbiddenCommand("[ERR] Buy command operates with the -q or -n flags.");
            }

            if(user != nullptr) {
                delete user;
            }
            if(order != nullptr) {
                delete order;
            }
        }
        else {
            throw CLIUtils :: AuthError("[ERR] Authentication failed.");
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
                throw CLIUtils :: ForbiddenCommand("[ERR] Sell command operates with the -q or -n flags.");
            }

        }
        else {
            throw CLIUtils :: AuthError("[ERR] Authentication failed.");
        }
    } 
    
    else {
        throw CLIUtils :: ForbiddenCommand("[ERROR] Bad input. Please choose either buy or sell options when using the instant interface.");
    }
}


Router :: ~Router() {
    if(this != nullptr) {
        for(auto mode : routes) {
            if(mode.second != nullptr) {
                delete mode.second;
                mode.second = nullptr;
            }
    }
    }
}

Mode :: ~Mode() {
    for(auto opt : options) {
            if(opt != nullptr) {
                delete opt;
                opt = nullptr;
            }
        }
}


// MAIN FUNC

int main(int argc, char** argv) {
    Router* router = new Router(argc, argv);                                                                                                                                                                       
    Instant* mode = new Instant(router);                                                                                                                                                                           
    Data* data = new Data(router);                                                                                                                                                                                 
                                                                                                                                                                                                                   
    Option* account = new Option("account");                                                                                                                                                                          
    InputOption* assetData = new InputOption("asset");                                                                                                                                                             
                                                                                                                                                                                                                   
    InputOption* auth = new InputOption("--auth");
    InputOption* dataAuth = new InputOption("--auth");                                                                                                                                                         
    InputOption* buy = new InputOption("buy");                                                                                                                                                                     
    InputOption* sell = new InputOption("sell");                                                                                                                                                                   
                                                                                                                                                                                                                                                                                                                                                                         
    InputOption* orderQuantity = new InputOption("-q");                                                                                                                                                            
    InputOption* orderNotional = new InputOption("-n");                                                                                                                                                                                                                                                                                                                
                                                                                                                                                         
                                                                                                                                                                                                                   
    mode->option(buy);                                                                                                                                                                                             
    mode->option(sell);                                                                                                                                                                                                                                                                                                                                                                 
    mode->option(orderQuantity);                                                                                                                                                                                   
    mode->option(orderNotional);                                                                                                                                                                                                                                                                                                                                                                
    mode->option(auth);  

    data->option(account);
    data->option(assetData);
    data->option(dataAuth);

    router->route("instant", mode);
    router->route("data", data);

    try {
        router->run();
        delete router;
    }
    catch (std :: exception& e) {
        std :: cout << e.what() << std :: endl;
        throw(e);
        delete router;
    }
    
    
}