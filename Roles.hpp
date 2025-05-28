#include "Game.hpp"
using namespace coup;

namespace coup {
	/*
	* Can see the number of coins another player has and prevent them from using the arrest action on their next turn.
	* This action costs no coins and does not count as a turn.
	*/
	class Spy : public Player {
		public:
			int see_coins(Player* target);
			void block_arrest(Player* target);
	};
	/* 
	 * Takes an additional coin when doing a tax action. Can cancel others' tax actions.
	 */
	class Governor : public Player {
	public:
		Action tax() override;
		void undo_tax();
	};
	/* 
	 * Can cancel bribes, and forces a person to pay 1 coin if attacked with a sanction.
	 */
	class Judge : public Player {
	public:
		void undo_bribe();
		void sanction_resp(Player* sender) override;
	};
	/*
	 * If he starts a turn with at least 3 coins, receives an extra coin for free.
	 * Additionally, if affected by arrest, pays two coins to the pool instead of another player.
	*/
	class Merchant : public Player {
	public:
		void start_turn() override;
		int arrest_resp() override;
	};
	/*
	 * Can "invest" 3 coins and receive 6 coins in return. 
	 * Additionally, if attacked with a sanction, receives one coin as compensation.
	 */
	class Baron : public Player {
	public:
		void invest();
		void sanction_resp(Player* sender) override;
	};
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
