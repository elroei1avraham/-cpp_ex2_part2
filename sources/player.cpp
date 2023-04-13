#include "player.hpp"
#include "game.hpp"
#include "card.hpp"

using namespace ariel;

// constractor
Player ::Player(string name)
{
    this->cardTaken = 0;
    this->name = name;
    this->countWinner = 0;
};

void Player ::setCard(int num, string str)
{
    // enter to the stack card we get 
    this->cards.push(*(new Card(num, str)));
}

string Player ::getName()
{
    // return the name of the player
    return this->name;
};

int Player ::getCountWinner()
{
    // return the count the player win
    return this->countWinner;
};

Card Player ::checkTopCard()
{
    // pop the card in the top of the stack and rturn this
    Card card = this->cards.top();
    this->cards.pop();
    return card;
};

void Player ::playerWin(int numberOfCards)
{
    // add the number of the cards the player win and add 1 to the counter win
    this->cardTaken += numberOfCards;
    this->countWinner++;
};

void Player ::drawInLasTurn(int numberOfCards)
{
    // if in the last turn of the game we have a draw we need to add to card taken but not the counter win
    this->cardTaken += numberOfCards;
};

int Player ::stacksize()
{
    // return the size of the stack
    return this->cards.size();
};

int Player ::cardesTaken()
{
    // return the connt of the cards that player take
    return this->cardTaken;
};