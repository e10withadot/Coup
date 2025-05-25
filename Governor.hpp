#include "Player.hpp"
using namespace coup;

namespace coup {
	/* 
	 * Takes an additional coin when doing a tax action. Can cancel others' tax actions.
	 */
	class Governor : public Player {
	public:
		Action tax() override;
		void undo_tax();
	};
}
