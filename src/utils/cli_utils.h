#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <iostream>
#include <string>
#include <exception>

using std::string;

namespace CLIUtils {

    inline void printInitMessage() {
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



    // EXCEPTIONS

// template from StackOverFlow: https://stackoverflow.com/questions/8152720/correct-way-to-inherit-from-stdexception
class ForbiddenCommand: public std::exception {
  public:
   explicit ForbiddenCommand(const char* message) : msg(message) {}
   ForbiddenCommand(ForbiddenCommand const&) noexcept = default;

   ForbiddenCommand& operator=(ForbiddenCommand const&) noexcept = default;
  ~ForbiddenCommand() override = default;

  const char* what() const noexcept override { return msg; }
 private:
  const char* msg;
};

class AuthError: public std::exception {
  public:
   explicit AuthError(const char* message) : msg(message) {}
   AuthError(AuthError const&) noexcept = default;

   AuthError& operator=(AuthError const&) noexcept = default;
  ~AuthError() override = default;

  const char* what() const noexcept override { return msg; }
 private:
  const char* msg;
};

class QueryError: public std::exception {
  public:
   explicit QueryError(const char* message) : msg(message) {}
   QueryError(QueryError const&) noexcept = default;

   QueryError& operator=(QueryError const&) noexcept = default;
  ~QueryError() override = default;

  const char* what() const noexcept override { return msg; }
 private:
  const char* msg;
};

class InternalError: public std::exception {
  public:
   explicit InternalError(const char* message) : msg(message) {}
   InternalError(InternalError const&) noexcept = default;

   InternalError& operator=(InternalError const&) noexcept = default;
  ~InternalError() override = default;

  const char* what() const noexcept override { return msg; }
 private:
  const char* msg;
};

}

#endif