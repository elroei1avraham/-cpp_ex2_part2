#include "card.hpp"
#include "game.hpp"

using namespace ariel;

// constractor
Card ::Card(int value, string suit)
{
    this->value = value;
    this->suit = suit;
};

int Card ::getValue()
{
    // return the value of the card
    return this->value;
};

string Card ::getSuit()
{
    // return the suit of the card
    return this->suit;
};

string Card ::getDetailsOfCard()
{
    // return the details of the card, and if it is 1,11,12,13 return the name of the card
    string details="";
    if (this->getValue()==1)
    {
        details+="Ace";
    } else if(this->getValue() == 11){
        details+="Prince";
    } else if(this->getValue() == 12){
        details+="Queen";
    } else if(this->getValue() == 13){
        details+="King";
    } else {
        details+=to_string(this->getValue());
    }
    details+=" of " + this->getSuit();
    return details;
};

int Card ::compareto(Card other)
{
    // compare the value of card, if p1 win return 1, if p2 win return -1, if we have a draw return 0.
    // if player have Ace he win all apart from 2.
    if(this->value == 1){
        if(other.value!=2){
            return 1;
        }
    } else if(other.value == 1){
        if(this->value!=2){
            return -1;
        }
    }
    if (this->value > other.value)
    {
        return 1;
    }
    else if (this->value < other.value)
    {
        return -1;
    }
    return 0;
};