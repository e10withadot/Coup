#include "Game.hpp"
using namespace coup;
#include <cstddef>
#include <stdexcept>
using namespace std;

void Player::start_turn() {
}

void Player::gather() {
    if (!ECONOMY) throw invalid_argument("Economy commands not allowed.");
    this->COINS++;
}

Action Player::tax() {
    if (!ECONOMY) throw invalid_argument("Economy commands not allowed.");
    this->COINS+=2;
    return Action(this, NULL, 2);
}

Action Player::arrest(Player* target) {
    if (!ARREST) throw invalid_argument("Arrest not allowed.");
    int amount = target->arrest_resp();
    this->COINS+=amount;
    return Action(this, target, amount);
}

int Player::arrest_resp() {
    this->COINS--;
    return 1;
}

Action Player::bribe() {
    this->ADDITIONAL = true;
    return Action(this, NULL, 0);
}

void Player::sanction(Player* target) {
    this->COINS-=3;
    target->sanction_resp(this);
}

void Player::sanction_resp(Player* sender) {
    this->ECONOMY= false;
}

Action Player::coup(Player* target) {
    target->coup_resp();
    return Action(this, target, 0);
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

void Player::mod_coins(int mod) {
    this->COINS+=mod;
}

Game* Player::game() {
    return this->CUR_GAME;
}
