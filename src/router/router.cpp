#include "./router.h"

// METHODS OF OPTION CLASS

void Option :: setRouter(Router* r) {
    router = r;
}

void Option :: setActive() {
    active = true;
}

Option :: operator bool() const {
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

/*
void Option :: incompatibleWith(string opt) {
    for(string option : this->incompatibleOptions) {
        if(opt == option) return;
    }
    incompatibleOptions.push_back(opt);
}
*/
// METHODS OF INPUTOPTION CLASS

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
    if(argc < 2) {
        std :: cerr << "First argument not found." << std :: endl;
        exit(1);
    } else {
        this->switchRoute();
    }    
    mode->run();
}

// METHODS OF INSTANT CLASS

void Instant :: run() {
    std :: cout << "Called the Instant interface." << std :: endl;
    Mode :: run();
}


// MAIN FUNC

int main(int argc, char** argv) {
    Router* router = new Router(argc, argv);

    InputOption* buy = new InputOption("buy");
    Option* dumm = new Option("dumm");
    Option* logging = new Option("--logging");
    
    Instant* mode = new Instant(router);
    mode->option(buy);
    mode->option(dumm);
    mode->option(logging);

    router->route("instant", mode);
    router->run();
    
}