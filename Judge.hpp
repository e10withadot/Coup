#include "Game.hpp"
using namespace coup;

namespace coup {
	/* 
	 * Can cancel bribes, and forces a person to pay 1 coin if attacked with a sanction.
	 */
	class Judge : public Player {
	public:
		void undo_bribe();
		void sanction_resp(Player* sender) override;
	};
}
