#include "Player.hpp"
#include <cstddef>
using namespace coup;

Action Player::gather() {
    this->COINS++;
    return Action(GATHER, NULL, 1);
}

Action Player::tax() {
    this->COINS+=2;
    return Action(TAX, NULL, 2);
}

Action Player::arrest(Player target) {
    int amount = target.arrest_resp();
    this->COINS+=amount;
    return Action(ARREST, &target, amount);
}

int Player::arrest_resp() {
    this->COINS--;
    return 1;
}

Action Player::sanction(Player target) {
    this->COINS-=3;
    target.sanction_resp();
    return Action(SANCTION, &target, 0);
}

void Player::sanction_resp() {
    this->economy= false;
}

Action Player::coup(Player target) {
    target.coup_resp();
    return Action(COUP, &target, 0);
}

int Player::coins() {
    return this->COINS;
}

Action Player::last_action() {
    return this->LAST_ACTION;
}
