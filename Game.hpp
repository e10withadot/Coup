#include "Player.hpp"
using namespace coup;
#include <string>
#include <vector>
using namespace std;

namespace coup {
	class Game {
	private:
		Player TURN;
		vector<Player> PLAYERS;
		Player WINNER;
	public:
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
