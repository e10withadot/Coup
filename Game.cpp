#include "Game.hpp"
#include <vector>
using namespace coup;

Player Game::turn() {
    return this->TURN;
}

vector<Player> Game::players() {
    return this->PLAYERS;
}

string Game::winner() {
    return this->WINNER.name();
}
