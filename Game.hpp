#ifndef GAME_H
#define GAME_H
#include "Player.hpp"
#include <QString>
using namespace coup;
#include <vector>
using namespace std;

namespace coup {
    enum ActionType {
        SEECOINS,
        GATHER,
        TAX,
        UNDOTAX,
        ARREST,
        BLOCKARREST,
        BRIBE,
        UNDOBRIBE,
        SANCTION,
        COUP,
        UNDOCOUP,
        INVEST
    };
    class Action {
        public:
            Action() : sender(nullptr), reciever(nullptr), coin_change(0) {}
            Action(ActionType type, Player* sender, Player* reciever, int coin_change) : type(type), sender(sender), reciever(reciever), coin_change(coin_change) {}
            Action(const Action& other) : type(other.type), sender(other.sender), reciever(other.reciever), coin_change(other.coin_change) {}
            ActionType type;
            Player* sender; 
            Player* reciever; 
            int coin_change;
    };
    class Game {
        private:
            Player* TURN;
            vector<Player*> PLAYERS;
            Action* LAST_TAX = nullptr;
            Action* LAST_ARREST = nullptr;
            Action* LAST_BRIBE = nullptr;
            Action* LAST_COUP = nullptr;
            Player* WINNER;
        public:
            Game(vector<Player*> players) : PLAYERS(players), TURN(players[0]), LAST_TAX(nullptr), LAST_ARREST(nullptr), LAST_BRIBE(nullptr), LAST_COUP(nullptr), WINNER(nullptr) {
                for (Player* p : players) {
                    p->setCurrentGame(this);
                }
            };
            ~Game();
            /*
             * Get last performed action according to type.
             */
            Action* getLast(ActionType type);
            /*
             * Set last performed action according to type.
             */
            void setLast(ActionType type, Action* val);
            /*
             * Gets the Player whose turn it is.
            */
            Player* turn();
            /*
             * Moves to the next player's turn.
            */
            void moveTurn();
            /*
             * Get all players currently playing or lost.
            */
            vector<Player*> players();
            /*
             * Get the name of the winning Player.
            */
            QString winner();
    };
}
#endif
