#include "Spy.hpp"
using namespace coup;

int Spy::see_coins(Player* target) {
    return target->coins();
}

void Spy::block_arrest(Player* target) {
    target->ARREST = false;
}
