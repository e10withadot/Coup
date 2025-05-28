#include "Game.hpp"
using namespace coup;

namespace coup {
	/*
	 * Can "invest" 3 coins and receive 6 coins in return. 
	 * Additionally, if attacked with a sanction, receives one coin as compensation.
	 */
	class Baron : public Player {
		public:
			void invest();
			void sanction_resp(Player* sender) override;
	};
}
