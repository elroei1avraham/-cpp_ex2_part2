#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <stack>
#include "card.hpp"

using namespace std;

class Player
{
private:
        string name;
        stack<Card> cards;
        int countWinner;
        int cardTaken;

public:
        Player(string name);
        void setCard(int num, string str);
        string getName();
        int getCountWinner();
        Card checkTopCard();
        void playerWin(int numberOfCards);
        void drawInLasTurn(int numberOfCards);
        int stacksize();
        int cardesTaken();
};

#endif