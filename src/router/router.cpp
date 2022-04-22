#include "./router.h"

Router :: Router(int argc, char** argv) : argc(argc), argv(argv) {
    std :: cout << "Running C01NS version 0.1" << std :: endl;
}

string Router :: getOpt(string opt, unsigned int atIndex) {
    if(atIndex) {
        if(argc < atIndex -1) {
            std :: cerr << "[ERROR] Index error." << std :: endl;
            exit(1);
        }
        return argv[atIndex];
    }
    for(int i = 1; i < argc; i++) {
        if(opt == argv[i]) {
            return argv[i];
        }
    }
    return "";
}

void Router :: switchRoute() {
    auto r = routes.find(this->getOpt("", 1));
    if(r != routes.end()) {
        std :: cout << "Route: " << r->first << std :: endl;
        this->mode = r->second;
    } else {
        std :: cerr << "[ERROR] Route not found." << std :: endl;
    }
}

void Router :: switchRoute(string route) {
    auto r = routes.find(route);
    if(r != routes.end()) {
        this->mode = r->second;
    } else {
        std :: cerr << "[ERROR] Route not found." << std :: endl;
    }
}

void Router :: route(string opt, Mode* mode) {
    routes.insert({opt, mode});
}

string Router :: listen(string opt) {
    string in;
    std :: cin >> in;
    return in;
}

void Router :: run() {
    if(argc < 2) {
        std :: cerr << "Please specify mode in your first argument: ";
        this->switchRoute(this->listen("mode"));
    } else {
        this->switchRoute();
    }    
    mode->run();
}

void Mode :: run() {
    std :: cout << "Called the mode obj." << std :: endl;
}

void Instant :: run() {
    std :: cout << "Called the instant interface" << std :: endl;
}

int main(int argc, char** argv) {
    Router router(argc, argv);

    router.route("instant", new Instant());
    router.run();
}