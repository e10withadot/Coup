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
		Player turn();
		vector<Player> players();
		string winner();
	};
}
