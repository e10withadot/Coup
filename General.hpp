#include "Game.hpp"
using namespace coup;

namespace coup {
	/*
	 * Can pay 5 coins to undo a coup against another player (or themselves).
	 * Additionally, if affected by arrest, receives back the coin that was taken.
	*/
	class General : public Player {
	public:
		void undo_coup();
		int arrest_resp() override;
	};
}
