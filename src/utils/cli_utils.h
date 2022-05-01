#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <iostream>
#include <string>

using std::string;

namespace CLIUtils {

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