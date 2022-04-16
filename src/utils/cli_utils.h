#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

using std::string;

namespace CLIUtils {

    class CommandLineApp {
        int argc;
        const char** argv;

        public:
        CommandLineApp(int argc, const char** argv) :argc(argc), argv(argv) {};

        virtual int findArg(const char* str) {
            for(int i = 1; i < argc; i++) {
                if(!strcmp(str, argv[i])) {
                    return i;
                }
            }
            return 0;
        }

        virtual const char* getArgValue(const char* str) {
            int idx = findArg(str);
            assert(idx < argc);
            if(idx) {
                return argv[idx+1];
            }
            else return "";
        }

        virtual const char* getUserInput(string message = "") {
            char* tmp;
            std::cout << message;
            std::cin >> tmp;
            return tmp;
        }

    };

    



    void printInitMessage() {
        std::cout << std::endl << "***************************************************" << std::endl 
            << R"(
 ██████╗ ██████╗  ██╗███╗   ██╗███████╗
██╔════╝██╔═████╗███║████╗  ██║██╔════╝
██║     ██║██╔██║╚██║██╔██╗ ██║███████╗
██║     ████╔╝██║ ██║██║╚██╗██║╚════██║
╚██████╗╚██████╔╝ ██║██║ ╚████║███████║
╚═════╝ ╚═════╝  ╚═╝╚═╝  ╚═══╝╚══════╝
//////// The alternative crypto trader. 
            )" << std::endl << "***************************************************" << std::endl << std::endl
            << "Created by: https://github.com/betonitcso" << std::endl
            << "Repo: https://github.com/betonitcso/c01ns"<< std::endl << std::endl
            << "[NOTE]  The author of the app is not responsible for any financial damage whatsoever." <<std::endl
            << "\tCrypto trading is dangerous, especially when it's done with sketchy 3rd party software." << std::endl
            << "\tUse C01NS at your own risk." << std::endl << std::endl
            << "***************************************************" << std::endl;

    };
}

#endif