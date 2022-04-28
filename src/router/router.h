#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>

using std::string;

class Router;
class Mode;
class Option;

class Mode {
protected:
    Router& router;
    std :: vector<Option*> options;
public:
    explicit Mode(Router& r);
    explicit Mode(Router* r);
    void option(Option* opt);
    bool getOpt(string opt);
    string getInputOpt(string opt);
    virtual void run();
};

class Option{
    bool active;
    string key;
    Router* router;
public:
    explicit Option(string key, bool defaultActive = false) : key(key), active(defaultActive) {};
    void setRouter(Router* r);
    string getKey();

    operator bool() const;
};

class InputOption : public Option {
    string value;
public:
    explicit InputOption(string key, string value = "", bool defaultActive = false) :Option(key, defaultActive), value(value) {};
    void setValue(string input);
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
    void switchRoute(string opt);
    Router& getRouter();
    string getArg(string arg, unsigned int atIndex = 0);
    string getArgValue(string arg, unsigned int atIndex = 0);
    unsigned int getArgIndex(string arg);
};

class Instant : public Mode {
public:
    Instant(Router& r) : Mode :: Mode(r) {};
    Instant(Router* r) : Mode :: Mode(r) {};
    void run();
};

class Strategy : public Mode {
public:
    void run();
};

#endif