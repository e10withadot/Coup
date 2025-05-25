#include "Player.hpp"
using namespace coup;

namespace coup {
	/*
	 * If he starts a turn with at least 3 coins, receives an extra coin for free.
	 * Additionally, if affected by arrest, pays two coins to the pool instead of another player.
	*/
	class Merchant : public Player {
	public:
		void start_turn() override;
		int arrest_resp() override;
	};
}
