#include "Game.hpp"
#include <cstddef>
using namespace coup;

void Player::gather() {
    this->COINS++;
}

Action Player::tax() {
    this->COINS+=2;
    return Action(this, NULL, 2);
}

Action Player::arrest(Player target) {
    int amount = target.arrest_resp();
    this->COINS+=amount;
    return Action(this, &target, amount);
}

int Player::arrest_resp() {
    this->COINS--;
    return 1;
}

void Player::sanction(Player target) {
    this->COINS-=3;
    target.sanction_resp();
}

void Player::sanction_resp() {
    this->ECONOMY= false;
}

Action Player::coup(Player target) {
    target.coup_resp();
    return Action(this, &target, 0);
}

void Player::coup_resp() {
    this->LOST= true;
}

string Player::name() {
    return this->NAME;
}

int Player::coins() {
    return this->COINS;
}
