#include "Roles.hpp"
#include "Game.hpp"
#include <iostream>
#include <stdexcept>
using namespace coup;

Action* Spy::see_coins(Player* target) {
    return new Action(SEECOINS, this, target, target->coins());
}

Action* Spy::block_arrest(Player* target) {
    target->ARREST = false;
    return new Action(BLOCKARREST, this, NULL, 3);
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

Action* Governor::tax() {
    this->COINS+=3;
    return new Action(TAX, this, NULL, 3);
}

Action* Governor::undo_tax() {
    Action* last_tax = this->game()->getLast(TAX);
    Player* target = last_tax->sender;
    int amount = last_tax->coin_change;
    target->mod_coins(-amount);
    return new Action(UNDOTAX, this, target, amount);
}

Action* General::undo_coup() {
    Action* last_coup = this->game()->getLast(COUP);
    Player *target = last_coup->reciever;
    target->LOST = false;
    return new Action(UNDOCOUP, this, target, 0);
}

int General::arrest_resp() {
    return 1;
}

Action* Baron::invest() {
    this->COINS+=3;
    return new Action(INVEST, this, NULL, 3);
}

void Baron::sanction_resp(Player* sender) {
    this->COINS++;
    this->Player::sanction_resp(sender);
}

Action* Judge::undo_bribe() {
    Action* last_bribe = this->game()->getLast(BRIBE);
    Player *target = last_bribe->sender;
    target->ADDITIONAL = false;
    return new Action(UNDOBRIBE, this, target, 0);
}

void Judge::sanction_resp(Player* sender) {
    sender->mod_coins(-1);
    this->Player::sanction_resp(sender);
}
