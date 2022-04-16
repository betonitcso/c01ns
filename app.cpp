#include <string>
#include <iostream>
#include <cstring>

#include "./src/utils/cli_utils.h"

using std::string;

class Client{};

enum Mode {
    paper,
    instant,
    strategy,
};


class App : public CLIUtils :: CommandLineApp {
    Mode mode;
    Client client;
    public:
        App(int argc, const char** argv) : CommandLineApp(argc, argv) {
            if(argc < 2) {
                std::cerr << "Not enough arguments given." << std::endl;
                exit(1);
            }
            handleMode();
        };
        
        void handleMode() {
            if(findArg("paper")) {
                mode = paper;
                
                if(!findArg("execute") || !findArg("user") || !findArg("data")) {
                    std::cout << "[ERROR] Paper trading can only be used with these commands: \n\texecute\n\t user\n\tdata" << std::endl;
                    exit(1);
                }
                std::cout << "[INFO] Mode set to paper trading." << std::endl;
            } else if (findArg("execute")) {
                mode = strategy;
            } else if (findArg("user")) {
                // call user data functions
            } else if (findArg("data")) {
                // call data functions
            } else if(findArg("instant")) {
                mode = instant;
            } else {
                std::cout << "[ERROR] Please enter a valid mode: \n\n\tinstant (default)\n\tpaper\n\texecute\n\tuser\n\tdata" << std::endl;
            }
        }
};


int main(int argc, const char** argv) {
    App app(argc, argv);
}