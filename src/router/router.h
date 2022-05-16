#ifndef ROUTER_H
#define ROUTER_H

// STANDARD LIB IMPORTS

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <stdexcept>

// 3RD PARTY IMPORTS
#include "../utils/json/single_include/nlohmann/json.hpp"
#include "../utils/jporta/Test/memtrace.h"
#include "../utils/jporta/Test/gtest_lite.h"

// PROJECT IMPORTS
#include "../assets/asset.h"
#include "../client/client.h"
#include "../orders/order.h"
#include "../user/user.h"
#include "../utils/crypto_utils.h"
#include "../utils/cli_utils.h"

using std::string;

// CLASS DECLARATIONS ( TO SHUT THE COMPILER UP )

class Router;
class Mode;
class Option;
class OptionCallback;


// OPTION & INPUTOPTION CLASSES
class Option{
protected:
    bool active;
    bool _callback;
    string key;

    Router* router;
    Mode* mode;
public:
    explicit Option(string key, bool defaultActive = false) : key(key), active(defaultActive) {};

    void setRouter(Router* r);
    string getKey();
    bool isActive();
    void setActive();
    operator bool() const;
};

class InputOption : public Option {
    string value;
public:
    explicit InputOption(string key, string value = "", bool defaultActive = false) :Option(key, defaultActive), value(value) {};

    void setValue(string input);
    string getValue();
};


// MODE CLASS

class Mode {
protected:
    Router& router;
public:
    std :: vector<Option*> options;
    explicit Mode(Router& r);
    explicit Mode(Router* r);
    ~Mode();
    void option(Option* opt);
    void option(string opt); // TODO:  THIS NEEDS TO BE DEFINED
    Option* getOpt(string opt);
    InputOption* getInputOpt(string opt);

    virtual void run();
};

// ROUTER CLASS

class Router {
    int argc;
    char** argv;
    std :: unordered_map<string, Mode*> routes;
    Mode* mode;
public:
    Router(int argc, char**argv);
    ~Router();
    void route(string opt, Mode* mode);
    void run();
    void switchRoute();
    void switchRoute(string opt);
    Router& getRouter();
    string getArg(string arg, unsigned int atIndex = 0);
    string getArgValue(string arg, unsigned int atIndex = 0);
    unsigned int getArgIndex(string arg);
};

// BUILT-IN MODES

class Instant : public Mode {
public:
    Instant(Router& r) : Mode :: Mode(r) {};
    Instant(Router* r) : Mode :: Mode(r) {};
    virtual void run();
};


class Data : public Mode {
public:
    Data(Router& r) : Mode :: Mode(r) {};
    Data(Router* r) : Mode :: Mode(r) {};
    virtual void run();
};

#endif