#ifndef CARD_HPP
#define CARD_HPP
#include <string>

using namespace std;

class Card
{
private:
    int value;
    string suit;

public:
    Card(int value, string suit);
    int getValue();
    string getSuit();
    string getDetailsOfCard();
    int compareto(Card other);
};

#endif