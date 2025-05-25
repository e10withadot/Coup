#include "Player.hpp"
using namespace coup;

namespace coup {
	/*
	 * Can "invest" 3 coins and receive 6 coins in return. 
	 * Additionally, if attacked with a sanction, receives one coin as compensation.
	 */
	class Baron : public Player {
	public:
		Action invest();
		Action sanction() override;
	};
}
