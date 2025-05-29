#ifndef GAME_H
#define GAME_H
#include "Player.hpp"
using namespace coup;
#include <string>
#include <vector>
using namespace std;

namespace coup {
	enum ActionType {
		TAX,
		ARREST,
		BRIBE,
		COUP
	};
	class Action {
		public:
			Action(Player* sender, Player* reciever, int coin_change) : sender(sender), reciever(reciever), coin_change(coin_change) {}
			Action(Action* other) : sender(other->sender), reciever(other->reciever), coin_change(other->coin_change) {}
			Player* sender; 
			Player* reciever; 
			int coin_change;
	};
	class Game {
		private:
			Player TURN = NULL;
			vector<Player> PLAYERS;
			Player WINNER = NULL;
			Action LAST_TAX;
			Action LAST_ARREST;
			Action LAST_BRIBE;
			Action LAST_COUP;
		public:
			Game(vector<Player> players) : PLAYERS(std::move(players)), LAST_TAX(NULL), LAST_ARREST(NULL), LAST_BRIBE(NULL), LAST_COUP(NULL) {};
			/*
			 * Get last performed action according to type.
			 */
			Action get_last(ActionType type);
			/*
			 * Set last performed action according to type.
			 */
			void set_last(ActionType type, Action val);
			/*
			 * Gets the Player whose turn it is.
			*/
			Player turn();
			/*
			 * Get all players currently playing or lost.
			*/
			vector<Player> players();
			/*
			 * Get the name of the winning Player.
			*/
			string winner();
	};
}
#endif
