#include "./router.h"

// Functions for Option class

void Option :: setRouter(Router* r) {
    router = r;
}

Option :: operator bool() const {
    if(router->getArg(key) != "") {
        return true;
    } else return false;
}

string Option :: getKey() {
    return this->key;
}

void InputOption :: setValue(string val) {
    value = val;
}

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
    if(argc < 2) {
        std :: cerr << "First argument not found.";
        exit(1);
    } else {
        this->switchRoute();
    }    
    mode->run();
}

Mode :: Mode(Router& r) :router(r.getRouter()) { }

Mode :: Mode(Router* r) : router(r->getRouter()) {} 

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
            std :: cout << "Option " << opt->getKey() << " found!!" << std :: endl;
        }
    }
}

void Instant :: run() {
    std :: cout << "Called the Instant interface." << std :: endl;
    Mode :: run();
}


int main(int argc, char** argv) {
    Router* router = new Router(argc, argv);

    Option* buyOption = new Option("buy");
    Option* sellOption = new Option("sell");
    
    Instant* mode = new Instant(router);
    mode->option(buyOption);
    mode->option(sellOption);



    router->route("instant", mode);
    router->run();
    
}