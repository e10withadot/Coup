#include "Player.hpp"
using namespace coup;

namespace coup {
	class Spy : public Player {
	public:
		void see_coins(Player target);
		void undo_arrest();
	};
}
