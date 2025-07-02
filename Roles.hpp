#ifndef ROLES_H
#define ROLES_H
#include "Game.hpp"
#include "Player.hpp"
using namespace coup;

namespace coup {
    /*
    * Can see the number of coins another player has and prevent them from using the arrest action on their next turn.
    * This action costs no coins and does not count as a turn.
    */
    class Spy : public Player {
    public:
        Spy(int index, bool cpu) : Player(index, cpu)  { this->ROLE = SPY; }
        Action* see_coins(Player* target);
        Action* block_arrest(Player* target);
    };
    /* 
     * Takes an additional coin when doing a tax action. Can cancel others' tax actions.
     */
    class Governor : public Player {
    public:
        Governor(int index, bool cpu) : Player(index, cpu)  { this->ROLE = GOVERNOR; }
        Action* tax() override;
        Action* undo_tax();
    };
    /* 
     * Can cancel bribes, and forces a person to pay 1 coin if attacked with a sanction.
     */
    class Judge : public Player {
    public:
        Judge(int index, bool cpu) : Player(index, cpu)  { this->ROLE = JUDGE; }
        Action* undo_bribe();
        void sanction_resp(Player* sender) override;
    };
    /*
     * If he starts a turn with at least 3 coins, receives an extra coin for free.
     * Additionally, if affected by arrest, pays two coins to the pool instead of another player.
    */
    class Merchant : public Player {
    public:
        Merchant(int index, bool cpu) : Player(index, cpu)  { this->ROLE = MERCHANT; }
        void start_turn() override;
        int arrest_resp() override;
    };
    /*
     * Can "invest" 3 coins and receive 6 coins in return. 
     * Additionally, if attacked with a sanction, receives one coin as compensation.
     */
    class Baron : public Player {
    public:
        Baron(int index, bool cpu) : Player(index, cpu)  { this->ROLE = BARON; }
        Action* invest();
        void sanction_resp(Player* sender) override;
    };
    /*
     * Can pay 5 coins to undo a coup against another player (or themselves).
     * Additionally, if affected by arrest, receives back the coin that was taken.
    */
    class General : public Player {
    public:
        General(int index, bool cpu) : Player(index, cpu)  { this->ROLE = GENERAL; }
        Action* undo_coup();
        int arrest_resp() override;
    };
}
#endif
