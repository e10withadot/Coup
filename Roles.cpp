#include "Roles.hpp"
using namespace coup;

int Spy::see_coins(Player* target) {
    return target->coins();
}

void Spy::block_arrest(Player* target) {
    target->ARREST = false;
}

void Merchant::start_turn() {
    if (this->COINS >= 3)
        this->COINS++;
    this->Player::start_turn();
}

int Merchant::arrest_resp() {
    this->COINS-=2;
    return 0;
}

Action Governor::tax() {
    this->COINS+=3;
    return Action(this, NULL, 3);
}

void Governor::undo_tax() {
    Action last_tax = this->game()->get_last(TAX);
    Player* target = last_tax.reciever;
    int amount = last_tax.coin_change;
    target->mod_coins(-amount);
}

void General::undo_coup() {
    Action last_coup = this->game()->get_last(COUP);
    Player *target = last_coup.reciever;
    target->LOST = false;
}

int General::arrest_resp() {
    return 1;
}

void Baron::invest() {
    this->COINS+=3;
}

void Baron::sanction_resp(Player* sender) {
    this->COINS++;
    this->Player::sanction_resp(sender);
}

void Judge::undo_bribe() {
    Action last_bribe = this->game()->get_last(BRIBE);
    Player *target = last_bribe.reciever;
    target->ADDITIONAL = false;
}

void Judge::sanction_resp(Player* sender) {
    sender->mod_coins(-1);
    this->Player::sanction_resp(sender);
}
