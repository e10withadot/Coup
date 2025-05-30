#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.hpp"
#include "Roles.hpp"
#include <vector>

TEST_CASE("Player basic functionality") {
    Spy* p1 = new Spy(0, false);
    Governor* p2 = new Governor(1, false);
    vector<Player*> players = {p1, p2};
    Game game(players);

    CHECK(p1->coins() == 0);
    CHECK(p1->index() == 0);
    CHECK(p1->role() == SPY);
    CHECK(p1->cpu() == false);

    Action* gather_action = p1->gather();
    CHECK(p1->coins() == 1);
    CHECK(gather_action->coin_change == 1);
    CHECK(gather_action->type == GATHER);
}

TEST_CASE("Game management") {
    Spy* p1 = new Spy(0, false);
    Governor* p2 = new Governor(1, false);
    vector<Player*> players = {p1, p2};
    Game game(players);

    CHECK(game.turn() == p1);
    game.moveTurn();
    CHECK(game.turn() == p2);
    CHECK(game.winner() == QString(""));
}

TEST_CASE("Spy abilities") {
    Spy* p1 = new Spy(0, false);
    Governor* p2 = new Governor(1, false);
    vector<Player*> players = {p1, p2};
    Game game(players);

    p2->COINS = 5;
    Action* see_action = p1->see_coins(p2);
    CHECK(see_action->type == SEECOINS);
    CHECK(see_action->coin_change == 5);

    Action* block_action = p1->block_arrest(p2);
    CHECK(block_action->type == BLOCKARREST);
    CHECK(p2->ARREST == false);
}

TEST_CASE("Governor abilities") {
    Governor* p1 = new Governor(0, false);
    Spy* p2 = new Spy(1, false);
    vector<Player*> players = {p1, p2};
    Game game(players);

    Action* tax_action = p1->tax();
    CHECK(tax_action->type == TAX);
    CHECK(tax_action->coin_change == 3);
    CHECK(p1->coins() == 3);
}

TEST_CASE("Baron abilities") {
    Baron* p1 = new Baron(0, false);
    Spy* p2 = new Spy(1, false);
    vector<Player*> players = {p1, p2};
    Game game(players);

    Action* invest_action = p1->invest();
    CHECK(invest_action->type == INVEST);
    CHECK(invest_action->coin_change == 3);
    CHECK(p1->coins() == 3);
}

TEST_CASE("General abilities") {
    General* p1 = new General(0, false);
    Spy* p2 = new Spy(1, false);
    vector<Player*> players = {p1, p2};
    Game game(players);

    p1->COINS = 7;
    Action* coup_action = p1->coup(p2);
    CHECK(coup_action->type == COUP);
    CHECK(p2->LOST == true);
    game.setLast(COUP, coup_action);

    p1->COINS = 5;
    Action* undo_action = p1->undo_coup();
    CHECK(undo_action->type == UNDOCOUP);
    CHECK(p2->LOST == false);
}

TEST_CASE("Judge abilities") {
    Judge* p1 = new Judge(0, false);
    Spy* p2 = new Spy(1, false);
    vector<Player*> players = {p1, p2};
    Game game(players);
    p1->COINS = 4;
    Action* bribe_action = p1->bribe();
    game.setLast(BRIBE, bribe_action);

    Action* undo_bribe = p1->undo_bribe();
    CHECK(undo_bribe->type == UNDOBRIBE);
    CHECK(p2->ADDITIONAL == false);
}

TEST_CASE("Merchant abilities") {
    Merchant* p1 = new Merchant(0, false);
    vector<Player*> players = {p1};
    Game game(players);

    p1->COINS = 3;
    p1->start_turn();
    CHECK(p1->coins() == 4);

    int arrest_response = p1->arrest_resp();
    CHECK(arrest_response == 0);
    CHECK(p1->coins() == 2);
}
