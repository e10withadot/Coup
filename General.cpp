#include "General.hpp"
using namespace coup;

void General::undo_coup() {
    Action last_coup = this->game()->get_last(COUP);
    Player *target = last_coup.reciever;
    target->LOST = false;
}

int General::arrest_resp() {
    return 1;
}
