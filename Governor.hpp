#include "Player.hpp"
using namespace coup;

namespace coup {
	class Governor : public Player {
	public:
		void tax() override;
		void undo_tax();
	};
}
