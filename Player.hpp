#ifndef PLAYER_H
#define PLAYER_H
namespace coup {
	class Game;
	class Action;
	class Player {
		protected:
			Game* CUR_GAME;
			bool CPU;
		public:
			int COINS = 0;
			bool ECONOMY = true;
			bool ARREST = true;
			bool ADDITIONAL = false;
			bool LOST = false;
			Player(bool CPU) : CPU(CPU) {};
			/*
			 * Function that runs when Player's turn starts.
			*/
			virtual void start_turn();
			/*
			 * Get one coin from the pool.
			*/
			void gather();
			/*
			 * Get two coins from the pool.
			*/
			virtual Action tax();
			/*
			 * Pay four coins to perform an additional action in the next turn.
			*/
			Action bribe();
			/*
			 * Get one coin from a different player.
			 * Cannot be used on the same player twice in a row.
			*/
			Action arrest(Player* target);
			/*
			 * Player's response to arrest.
			 */
			virtual int arrest_resp();
			/* 
			 * Blocks a player from performing economic actions. Costs 3 coins.
			*/
			virtual void sanction(Player* target);
			/*
			 * Player's response to sanction.
			 */
			virtual void sanction_resp(Player* sender);
			/*
			 * Eliminates a player from the game. Costs 7 coins.
			*/
			Action coup(Player* target);
			/*
			 * Player's response to coup.
			 */
			virtual void coup_resp();
			/*
			 * Get the player's current amount of coins.
			*/
			int coins();
			/*
			 * Modify the player's current amount of coins.
			*/
			void mod_coins(int mod);
			/*
			 * Get the current game.
			*/
			Game* game();
	};
}
#endif
