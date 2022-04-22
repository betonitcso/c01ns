#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using std::string;

class Mode {
public:
    virtual void run();
    virtual void option();
};

class Instant : public Mode {
public:
    void run();
};


class Router {
    int argc;
    char** argv;
    std :: unordered_map<string, Mode*> routes;
    Mode* mode;
public:
    Router(int argc, char**argv);

    void route(string opt, Mode* mode);
    void run();
    void switchRoute();
    void switchRoute(string route);

    string listen(string opt);
    unsigned int seekOpt(string opt);
    string getOpt(string opt, unsigned int atIndex = 0);
};

#endif