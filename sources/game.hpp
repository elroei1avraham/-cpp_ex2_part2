#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <iostream>
#include <array>
#include "player.hpp"
#include "card.hpp"

using namespace std;
namespace ariel
{
}

const int TypeOfNumCard = 13;
const int TypeOfSuitCard = 4;

class Game
{
private:
    Player &p1;
    Player &p2;
    string lastTurn;
    string historyOfTurn;
    int draw;

public:
    Game(Player &p1, Player &p2);
    void Startgame(Player &p1, Player &p2);
    void getCardToPlayer(Player &player, std::array<std::array<int, TypeOfSuitCard>, TypeOfNumCard> &arrayOfCards);
    void playTurn();
    void P1WinToQueue(Player p1,Card cardP1, Player p2, Card cardP2, string turn);
    void P2WinToQueue(Player p1,Card cardP1, Player p2, Card cardP2, string turn);
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
};

#endif