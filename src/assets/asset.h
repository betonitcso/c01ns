#ifndef ASSET_H
#define ASSET_H

#include <string>

using std::string;

class Asset {
    protected:
        string id;
        string symbol;
        string assetClass;
        string exchange;
        string status;
        bool tradable;
        bool marginable;
        bool shortable;
        bool easyToBorrow;
        bool fractionable;
    public:
}



#endif