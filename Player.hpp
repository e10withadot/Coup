namespace coup {
	class Player {
		public:
		virtual void start_turn();
		void gather();
		virtual void tax();
		void bribe();
		int coins();
		void arrest(Player target);
		void sanction(Player target);
		void coup(Player target);
	};
}
