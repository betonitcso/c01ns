#include "./router.h"

// Functions for Option class

void Option :: setActive() {
    active = true;
}

bool Option :: isActive() {
    return active;
}

string Option :: getKey() {
    return this->key;
}

bool operator==(Option& opt1, Option& opt2) {
    if(opt1.getKey() == opt2.getKey()) {
        return true;
    } return false;
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

void Mode :: option(Option* opt) {
    options.insert(opt);
}

void Mode :: run() {
    for(Option* opt : options) {
        if(router.getArg(opt->getKey()) != "") {
            opt->setActive();
        }
    }
}

void Instant :: run() {
    std :: cout << "Called the Instant interface." << std :: endl;
    Mode :: run();
}

void Strategy :: run() {
    std :: cout << "Called the Strategy interface."  << std :: endl;
}

void Data :: run() {
    std :: cout << "Called the Data interface." << std :: endl;
}

int main(int argc, char** argv) {
    Router router(argc, argv);

    Option* myOption = new Option("printMe", true);
    InputOption* myInputOption = new InputOption("-name", "buy");
    
    Instant* mode = new Instant(router);
    mode->option(myOption);
    mode->option(myInputOption);

    router.route("instant", mode);
    router.run();
    
}