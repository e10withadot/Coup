#include "Game.hpp"
using namespace coup;
#include <stdexcept>
#include <vector>
#include <iostream>
using namespace std;

Game::~Game() {
    delete this->LAST_TAX;
    delete this->LAST_ARREST;
    delete this->LAST_BRIBE;
    delete this->LAST_COUP;
}

Action* Game::getLast(ActionType type){
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
            throw invalid_argument("Invalid type.");
    };
}

void Game::setLast(ActionType type, Action* val){
    switch (type) {
        case TAX:
            LAST_TAX= val;
            break;
        case ARREST:
            LAST_ARREST= val;
            break;
        case BRIBE:
            LAST_BRIBE= val;
            break;
        case COUP:
            LAST_COUP= val;
            break;
        default:
            break;
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
        if (LAST_COUP->reciever->index() == index) LAST_COUP = nullptr;
        if (PLAYERS.size() == 1) WINNER = PLAYERS[0];
        else moveTurn();
    }
    else TURN = PLAYERS[index];
}

vector<Player*> Game::players() {
    return this->PLAYERS;
}

QString Game::winner() {
    if (WINNER != nullptr) return (QString("Player %1")).arg(WINNER->index()+1);
    else return QString("");
}
