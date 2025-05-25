#include "Player.hpp"
using namespace coup;

namespace coup {
	/*
	* Can see the number of coins another player has and prevent them from using the arrest action on their next turn.
	* This action costs no coins and does not count as a turn.
	*/
	class Spy : public Player {
	public:
		void see_coins(Player target);
		void undo_arrest();
	};
}
