#include "Merchant.hpp"
using namespace coup;

void Merchant::start_turn() {
    if (this->COINS >= 3)
        this->COINS++;
    this->Player::start_turn();
}

int Merchant::arrest_resp() {
    this->COINS-=2;
    return 0;
}
