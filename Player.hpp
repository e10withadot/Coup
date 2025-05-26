namespace coup {
	class Player;
	enum ActionType {
		GATHER,
		TAX,
		ARREST,
		SANCTION,
		INVEST,
		COUP
	};
	class Action {
		public:
		Action(ActionType type, Player* target, int coin_change) {
			this->type = type;
			this->target = target;
			this->coin_change = coin_change;
		}
		ActionType type;
		Player* target;
		int coin_change;
	};
	class Player {
		private:
			int COINS = 0;
			Action LAST_ACTION;
			bool ECONOMY = true;
			bool LOST = false;
		public:
			/*
			 * Function that runs when Player's turn starts.
			*/
			virtual void start_turn();
			/*
			 * Get one coin from the pool.
			*/
			Action gather();
			/*
			 * Get two coins from the pool.
			*/
			virtual Action tax();
			/*
			 * Pay four coins to perform an additional action.
			*/
			void bribe();
			/*
			 * Get one coin from a different player.
			 * Cannot be used on the same player twice in a row.
			*/
			Action arrest(Player target);
			/*
			 * Player's response to arrest.
			 */
			virtual int arrest_resp();
			/* 
			 * Blocks a player from performing economic actions. Costs 3 coins.
			*/
			Action sanction(Player target);
			/*
			 * Player's response to sanction.
			 */
			virtual void sanction_resp();
			/*
			 * Eliminates a player from the game. Costs 7 coins.
			*/
			Action coup(Player target);
			/*
			 * Player's response to coup.
			 */
			virtual void coup_resp();
			/*
			 * Get the player's current amount of coins.
			*/
			int coins();
			/*
			 * Get the player's last action.
			*/
			Action last_action();
	};
}
