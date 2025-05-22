#include "Player.hpp"
using namespace coup;

namespace coup {
	class Merchant : public Player {
	public:
		void start_turn() override;
	};
}
