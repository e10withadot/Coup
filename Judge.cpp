#include "Judge.hpp"
using namespace coup;

void Judge::undo_bribe() {
    Action last_bribe = this->game()->get_last(BRIBE);
    Player *target = last_bribe.reciever;
    target->ADDITIONAL = false;
}

void Judge::sanction_resp(Player* sender) {
    sender->mod_coins(-1);
    this->Player::sanction_resp(sender);
}
