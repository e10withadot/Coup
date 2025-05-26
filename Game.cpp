#include "Game.hpp"
#include <stdexcept>
#include <vector>
using namespace coup;

Action Game::get_last(ActionType type){
    switch (type) {
        case TAX:
            return this->LAST_TAX;
        case ARREST:
            return this->LAST_ARREST;
        case BRIBE:
            return this->LAST_BRIBE;
        case COUP:
            return this->LAST_COUP;
        default:
            throw invalid_argument("Invalid action type.");
    };
}

void Game::set_last(ActionType type, Action val){
    switch (type) {
        case TAX:
            this->LAST_TAX= val;
        case ARREST:
            this->LAST_ARREST= val;
        case BRIBE:
            this->LAST_BRIBE= val;
        case COUP:
            this->LAST_COUP= val;
        default:
            throw invalid_argument("Invalid action type.");
    };
}

Player Game::turn() {
    return this->TURN;
}

vector<Player> Game::players() {
    return this->PLAYERS;
}

string Game::winner() {
    return this->WINNER.name();
}
