#include "Player.hpp"
using namespace coup;
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
			Action(Player* sender, Player* reciever, int coin_change) {
				this->sender = sender;
				this->reciever = reciever;
				this->coin_change = coin_change;
			}
			Player* sender; 
			Player* reciever; 
			int coin_change;
	};
	class Game {
		private:
			Player TURN;
			vector<Player> PLAYERS;
			Player WINNER;
			Action LAST_TAX;
			Action LAST_ARREST;
			Action LAST_BRIBE;
			Action LAST_COUP;
		public:
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
