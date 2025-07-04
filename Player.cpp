#include "Player.hpp"
#include "Game.hpp"
using namespace coup;
#include <cstddef>
#include <stdexcept>
using namespace std;

void Player::setCurrentGame(Game* game) {
    CUR_GAME = game;
}
void Player::start_turn() {}

Action* Player::gather() {
    if (!ECONOMY) throw invalid_argument("Economy commands not allowed.");
    this->COINS++;
    return new Action(GATHER, this, nullptr, 1);
}

Action* Player::tax() {
    if (!ECONOMY) throw invalid_argument("Economy commands not allowed.");
    this->COINS+=2;
    return new Action(TAX, this, NULL, 2);
}

Action* Player::arrest(Player* target) {
    if (!ARREST) throw invalid_argument("Arrest not allowed.");
    int amount = target->arrest_resp();
    this->COINS+=amount;
    return new Action(ActionType::ARREST, this, target, amount);
}

int Player::arrest_resp() {
    this->COINS--;
    return 1;
}

Action* Player::bribe() {
    this->COINS-=4;
    this->ADDITIONAL = true;
    return new Action(BRIBE, this, NULL, 0);
}

Action* Player::sanction(Player* target) {
    this->COINS-=3;
    target->sanction_resp(this);
    return new Action(SANCTION, this, NULL, 0);
}

void Player::sanction_resp(Player* sender) {
    this->ECONOMY= false;
}

Action* Player::coup(Player* target) {
    target->coup_resp();
    return new Action(COUP, this, target, 0);
}

void Player::coup_resp() {
    this->LOST= true;
}

int Player::index() {
    return this->INDEX;
}

PlayerRole Player::role() {
    return this->ROLE;
}

bool Player::cpu() {
    return this->CPU;
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
