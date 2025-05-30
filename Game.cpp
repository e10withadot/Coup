#include "Game.hpp"
using namespace coup;
#include <stdexcept>
#include <vector>
using namespace std;

Action Game::getLast(ActionType type){
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

void Game::setLast(ActionType type, Action val){
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

Player* Game::turn() {
    return this->TURN;
}

void Game::moveTurn() {
    int index;
    if (TURN->index()+1 == PLAYERS.size())
        index = 0;
    else index = TURN->index()+1;
    if(PLAYERS[index]->LOST) {
        PLAYERS.erase(PLAYERS.begin() + index);
        if (PLAYERS.size() == 1) WINNER = PLAYERS[0];
        else moveTurn();
    }
    else TURN = PLAYERS[index];
}

vector<Player*> Game::players() {
    return this->PLAYERS;
}

QString Game::winner() {
    if (WINNER != nullptr) return (QString("Player %1")).arg(WINNER->index());
    else return QString("");
}
