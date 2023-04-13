#include "game.hpp"
#include <queue>
#define Hearts 1
#define Diamonds 2
#define Clubs 3
#define Spades 4

using namespace ariel;
using namespace std;

int getRandomNumber(int min, int max)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(nullptr));
        initialized = true;
    }
    return min + (rand() % (max - min + 1));
}

// Constractor

Game ::Game(Player &p1, Player &p2) : p1(p1), p2(p2)
{
    this->historyOfTurn = "";
    this->lastTurn = "";
    this->draw = 0;
    Startgame(this->p1, this->p2);
};

void Game ::Startgame(Player &p1, Player &p2)
{
    // Array for the all Cards, each card have 4 shapes
    int arrayOfCards[TypeOfNumCard][TypeOfSuitCard] = {{Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades},
                                                       {Hearts, Diamonds, Clubs, Spades}};
    // Convert C-style array to array(for make tidy)
    array<array<int, 4UL>, 13UL> stdArrayOfCards;
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            stdArrayOfCards[static_cast<array<array<int, 4UL>, 13UL>::size_type>(i)]
                           [static_cast<array<array<int, 4UL>, 13UL>::size_type>(j)] = arrayOfCards[i][j];
        }
    }

    // doing the dealing to players
    for (int i = 0; i < 26; i++)
    {
        getCardToPlayer(p1, stdArrayOfCards);
        getCardToPlayer(p2, stdArrayOfCards);
    }
}

void Game ::getCardToPlayer(Player &rplayer, array<array<int, 4UL>, 13UL> &arrayOfCards)
{
    int numCard;
    bool playerGetCard = false;
    // while the player not get a card enter the loop
    while (!playerGetCard)
    {
        // get random of card from the packet
        numCard = getRandomNumber(0, 51);
        int suitCard = numCard / TypeOfNumCard;
        // check if the card in the packet yet(with cast for make tidy)
        if (arrayOfCards[static_cast<array<array<int, 4UL>, 13UL>::size_type>(numCard) % TypeOfNumCard]
                        [static_cast<array<array<int, 4UL>, 13UL>::size_type>(suitCard)] != 0)
        {
            // add the card to player with the the correct shape
            if (suitCard + 1 == Hearts)
            {
                rplayer.setCard(numCard % TypeOfNumCard + 1, "Hearts");
            }
            else if (suitCard + 1 == Diamonds)
            {
                rplayer.setCard(numCard % TypeOfNumCard + 1, "Diamonds");
            }
            else if (suitCard + 1 == Clubs)
            {
                rplayer.setCard(numCard % TypeOfNumCard + 1, "Clubs");
            }
            else if (suitCard + 1 == Spades)
            {
                rplayer.setCard(numCard % TypeOfNumCard + 1, "Spades");
            }
            // enter in the certain index in the array 0 which indicates the card in not in the packet
            arrayOfCards[static_cast<std::array<std::array<int, 4UL>, 13UL>::size_type>(numCard) % TypeOfNumCard]
                        [static_cast<std::array<std::array<int, 4UL>, 13UL>::size_type>(suitCard)] = 0;
            playerGetCard = true;
        }
    }
}

void Game ::playTurn()
{
    // if the players are the same throw runtime error
    if (&this->p1 == &this->p2)
    {
        throw runtime_error("the tow player are the same player");
    }
    else
    {
        int numberOfCards = 0;
        // if the player have cards
        if (p1.stacksize() != 0 || p2.stacksize() != 0)
        {
            // getting the top card from the players
            Card cardP1 = p1.checkTopCard();
            Card cardP2 = p2.checkTopCard();

            // counter the cards was play in this turn
            numberOfCards += 2;

            // check who win in this turn or we have draw
            if (cardP1.compareto(cardP2) == 1)
            {
                cout << "p1 win" << endl;

                // the player 1 getting all of cards
                p1.playerWin(numberOfCards);

                // enter to the stirng last turn what happend in the last turn
                P1WinToQueue(this->p1, cardP1, this->p2, cardP2, "");
            }
            else if (cardP1.compareto(cardP2) == -1)
            {
                cout << "p2 win" << endl;

                // the player 2 getting all of cards
                p2.playerWin(numberOfCards);

                // enter to the stirng last turn what happend in the last turn
                P2WinToQueue(this->p1, cardP1, this->p2, cardP2, "");
            }
            else
            {
                string turnDraw="";

                // if we have another draw doing the while
                while (cardP1.compareto(cardP2) == 0)
                {
                    cout << "draw" << endl;
                    // adding 1 to counter of draw
                    this->draw++;
                    turnDraw += this->p1.getName() +
                                " played " + cardP1.getDetailsOfCard() + " " +
                                this->p2.getName() + " played " + cardP2.getDetailsOfCard() + ". " + "Draw. ";
                    
                    // if the player have enough cards for this turn play the draw
                    if (p1.stacksize() > 1 || p2.stacksize() > 1)
                    {
                        p1.checkTopCard();
                        p2.checkTopCard();
                        cardP1 = p1.checkTopCard();
                        cardP2 = p2.checkTopCard();
                        numberOfCards += 4;
                    } else{
                        break;
                    }
                }

                // if after the draw player1 win
                if (cardP1.compareto(cardP2) == 1)
                {
                    cout << "p1 win" << endl;
                    p1.playerWin(numberOfCards);
                    P1WinToQueue(this->p1, cardP1, this->p2, cardP2, turnDraw);
                }

                // if after the draw player2 win
                else if (cardP1.compareto(cardP2) == -1)
                {
                    cout << "p2 win" << endl;
                    p2.playerWin(numberOfCards);
                    P2WinToQueue(this->p1, cardP1, this->p2, cardP2, turnDraw);
                }
                // if the stack is over in the middle of the draw turn
                else
                {
                    if (p1.stacksize() == 1 && p2.stacksize() == 1)
                    {
                        p1.checkTopCard();
                        p2.checkTopCard();
                        numberOfCards += 2;
                        this->draw++;
                    }
                    p1.drawInLasTurn(numberOfCards / 2);
                    p2.drawInLasTurn(numberOfCards / 2);
                }
            }
        }
        // if the player dint have cards
        else
        {
            throw runtime_error("not have more cards");
        }
    }
};

// the functions is define the string of last turn and add the string to the history  
void Game ::P1WinToQueue(Player p1, Card cardP1, Player p2, Card cardP2, string turn)
{
    this->lastTurn = (turn + this->p1.getName() +
                      " played " + cardP1.getDetailsOfCard() + " " +
                      this->p2.getName() + " played " + cardP2.getDetailsOfCard() + ". " + this->p1.getName() + " wins.\n");
    this->historyOfTurn += this->lastTurn;
}

void Game ::P2WinToQueue(Player p1, Card cardP1, Player p2, Card cardP2, string turn)
{
    this->lastTurn = (turn + this->p1.getName() +
                      " played " + cardP1.getDetailsOfCard() + " " +
                      this->p2.getName() + " played " + cardP2.getDetailsOfCard() + ". " + this->p2.getName() + " wins.\n");
    this->historyOfTurn += this->lastTurn;
}

// the function print the last turn
void Game ::printLastTurn()
{
    // if the game not start
    if (this->lastTurn == "")
    {
        throw runtime_error("the game not start");
    }
    cout << this->lastTurn << endl;
};

void Game ::playAll()
{
    // while the player have card do the function playTurn()
    while (p1.stacksize() != 0 || p2.stacksize() != 0)
    {
        playTurn();
    }
};

void Game ::printWiner()
{
    // if the game not start we dont have a winner
    if (this->historyOfTurn == "")
    {
        throw runtime_error("the game not have winner yet");
    }
    if (p1.cardesTaken() > p2.cardesTaken())
    {
        cout << "the big winner is: " + p1.getName() << endl;
    }
    else if (p1.cardesTaken() < p2.cardesTaken())
    {
        cout << "the big winner is: " + p2.getName() << endl;
    }
    else
    {
        cout<<"the game end in a draw"<<endl;
    }
};

void Game ::printLog()
{
    // if the game not start throw runtime error
    if (this->historyOfTurn == "")
    {
        throw runtime_error("the game not start");
    }
    // print the history of turns
    cout << this->historyOfTurn << endl;
};

void Game ::printStats()
{
    // if the game not start throw runtime error
    if (this->historyOfTurn == "")
    {
        throw runtime_error("the game not end");
    }
    // print the stats the win ,the lose and the draw
    cout << this->p1.getName() + ":" << endl
         << "win: " + to_string(this->p1.getCountWinner()) +
                " lose: " + to_string(this->p2.getCountWinner()) +
                " draw:" + to_string(this->draw)
         << endl
         << this->p2.getName() + ":" << endl
         << "win: " + to_string(this->p2.getCountWinner()) +
                " lose: " + to_string(this->p1.getCountWinner()) +
                " draw:" + to_string(this->draw)
         << endl;
};