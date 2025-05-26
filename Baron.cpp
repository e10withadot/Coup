#include "Baron.hpp"
using namespace coup;

void Baron::invest() {
    this->COINS+=3;
}

void Baron::sanction_resp(Player* sender) {
    this->COINS++;
    this->Player::sanction_resp(sender);
}
