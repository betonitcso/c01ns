#ifndef ROUTER_H
#define ROUTER_H

// STANDARD LIB IMPORTS

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>

// 3RD PARTY IMPORTS
/*
*
*/

// PROJECT IMPORTS
/*
*
*/


using std::string;

// CLASS DECLARATIONS ( TO SHUT THE COMPILER UP )

class Router;
class Mode;
class Option;
class OptionCallback;

// OPTION CALLBACK

// OPTION & INPUTOPTION CLASSES
class Option{
protected:
    bool active;
    string key;
    Router* router;
public:
    explicit Option(string key, bool defaultActive = false) : key(key), active(defaultActive) {};
    void setRouter(Router* r);
    string getKey();
    bool isActive();
    bool hasCallback();
    void setActive();
    void operator() ();
    void notCompatibleWith(string opt);
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
    std :: vector<Option*> options;
public:
    explicit Mode(Router& r);
    explicit Mode(Router* r);

    void option(Option* opt);
    void option(string opt); // THIS NEEDS TO BE DEFINED
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

// WRITE CUSTOM MODES HERE

#endif