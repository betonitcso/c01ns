#include "./user.h"

int main() {
    auto user = new User("MYAPIKEY", "MYAPISECRET");
    auto btc = user->getAsset("btc");
    btc->info();
    user->order()
}