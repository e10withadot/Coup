#include "Governor.hpp"

Action Governor::tax() {
    this->COINS+=3;
    return Action(this, NULL, 3);
}

void Governor::undo_tax() {
    Action last_tax = this->CUR_GAME->get_last(TAX);
    Player* target = last_tax.reciever;
    int amount = last_tax.coin_change;
    target->mod_coins(-amount)
}
