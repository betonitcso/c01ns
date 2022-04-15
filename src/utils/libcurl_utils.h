#ifndef WRITECALLBACK_H
#define WRITECALLBACK_H

#include <string>
#include <curl/curl.h>

using std::string;

namespace LibcurlUtils {
     size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }  // this is from StackOverFlow
}



#endif