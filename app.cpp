#include <string>
#include <iostream>
#include <cstring>

#include "./src/utils/cli_utils.h"

using std::string;

enum Mode {
    instant,
    strategy,
    user,
    data
};


class App {

};

class ClientHandler {
    Mode mode;
    public:
        ClientHandler(int argc, const char* argv[]) {
            CLIUtils :: printInitMessage();

            if(argc < 2) {
                std::cerr << "[ERROR] No arguments given. See -h or --help for more." << std::endl;
                exit(1);
            }

            if(!strcmp(argv[1], "buy") || !strcmp(argv[1], "sell")) {
                std::cout << "You've called the C01NS instant interface." << std::endl;
            } else if(!strcmp(argv[1], "execute")) {
                std::cout << "You've called the C01NS trading strategy interface." << std::endl;
            } else if(!strcmp(argv[1], "user")) {
                std::cout << "You've called the C01NS user data interface." << std::endl;
            } else if(!strcmp(argv[1], "data")) {
                std::cout << "You've called the C01ns market data interface." << std::endl;
            } else {
                std::cout << "Invalid arguments. Type -help for help." << std::endl << std::endl;
                exit(1);
            }
        }
};


int main(int argc, const char* argv[]) {
    ClientHandler(argc, argv);
}