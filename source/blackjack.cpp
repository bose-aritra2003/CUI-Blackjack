#include "define.h"

//Ignores any data remaining in the input buffer
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Get the value of the chosen card according to blackjack rules
int getCardValue(const Card& card)
{
    switch(card.rank)
    {   //Ace could also have value 1 based on player's choice
        case Rank::two  :   return 2 ;
        case Rank::three:   return 3 ;
        case Rank::four :   return 4 ;
        case Rank::five :   return 5 ;
        case Rank::six  :   return 6 ;
        case Rank::seven:   return 7 ;
        case Rank::eight:   return 8 ;
        case Rank::nine :   return 9 ;
        case Rank::ten  :
        case Rank::jack :
        case Rank::queen:
        case Rank::king :   return 10;
        case Rank::ace  :   return 11;

        default:
            assert(false && "\nThis should never happen\n");
    }
}

//Check whether player wants to hit or stand
bool playerWantHit()
{
    while(true)
    {
        std::cout << "Enter (h) to hit & (s) to stand: ";
        char choice{};
        std::cin >> choice;

        switch (choice)
        {
            case 'h':
                return true;
            case 's':
                return false;
            default:
                std::cout << "--------------------------------------\n";
                std::cout << "Invalid choice! Enter choice again. \n";
                std::cout << "--------------------------------------\n";
                ignoreLine();
        }
    }
}

//Add value 1 or 11 according to respective choices when ace gets selected
bool aceChoice()
{
    while(true)
    {
        std::cout << "You got an Ace.\n";
        std::cout << "Enter (a) to add value 1 and "
                     "enter (b) to add value 11 to your current score: ";
        char choice{};
        std::cin >> choice;

        switch (choice)
        {
            case 'a':
                return true;
            case 'b':
                return false;
            default:
                std::cout << "--------------------------------------\n";
                std::cout << "Invalid choice! Enter choice again. \n";
                std::cout << "--------------------------------------\n";
                ignoreLine();
        }
    }
}

bool playerTurn(const deck_t& deck, Player& player, int& index)
{
    while (true)
    {
        if(player.score > maxValue)
        {
            std::cout << "You're busted ! \n";
            return true; //Player busted
        }
        else
        {
            if (playerWantHit())
            {
                printCard(deck[index]);
                std::cout << '\n';
                int cardValue{getCardValue(deck[index])};

                if(cardValue == ace_11)
                {
                    cardValue = (aceChoice()) ? ace_1 : ace_11;
                }

                player.score += cardValue;
                std::cout << "You were dealt a " << cardValue << '\n';
                std::cout << "Current score: " << player.score << "\n\n";
                ++index;
            }

            else
                return false; //Player wasn't busted
        }
    }

}

bool dealerTurn(const deck_t& deck, Player& dealer, int& index)
{
    while (true)
    {
        if(dealer.score > maxValue)
        {
            std::cout << "Dealer busted ! \n";
            return true; //Dealer busted
        }
        else
        {
            if (dealer.score < minValue)
            {
                sleep(3);
                printCard(deck[index]);
                std::cout << '\n';
                int cardValue{getCardValue(deck[index])};
                if(cardValue == ace_11)
                {
                    cardValue = (dealer.score > limit_ace) ? ace_1 : ace_11;
                }
                dealer.score += cardValue;
                std::cout << "Dealer was dealt a " << cardValue << '\n';
                std::cout << "Dealer's current score: " << dealer.score << "\n\n";
                ++index;
            }
            else
                return false; //Dealer wasn't busted
        }
    }

}


int playBlackjack(const deck_t& deck)
{
    int index{0};
    Player player, dealer;

    std::cout << "\n=========== Your Turn ===============\n";
    bool player_bust{playerTurn(deck, player, index)};
    if(player_bust)
        return 0;   //If player bursts he/she loose immediately

    //The following statements execute only if player is not busted

    std::cout << "\n=========== Dealer's Turn ===========\n";
    bool dealer_bust{dealerTurn(deck, dealer, index)};

    if (((player.score < dealer.score) && !dealer_bust))
    {
        return 0;   //Player loose
    }
    else if(player.score == dealer.score)
    {
        return 1;   //It's a tie
    }
    else if((player.score > dealer.score) || dealer_bust)
    {
        return 2;   //Player win
    }

    return 3; //If any case is missing
}

void executeGame(const deck_t& deck)
{
    switch (playBlackjack(deck))
    {
        case 0:
            std::cout << "You loose ! \n";
            break;
        case 1:
            std::cout << "It's a tie ! \n";
            break;
        case 2:
            std::cout << "You win ! \n";
            break;
        case 3: //If any case is missing then error will be shown
            std::cerr << "ERROR! Unknown state. \n";
            break;
    }
}

