#include "define.h"

//Ignores any data remaining in the input buffer
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Check whether player wants to hit or stand
bool playerWantsHit()
{
    while(true)
    {
        std::cout << "Enter (h) to hit & (s) to stand: ";
        char choice{};
        std::cin >> choice;
        std::cout << '\n';
        switch (choice)
        {
            case 'h':
                ignoreLine();
                return true;
            case 's':
                ignoreLine();
                return false;
            default:
                std::cout << "--------------------------------------\n";
                std::cout << "Invalid choice! Enter choice again. \n";
                std::cout << "--------------------------------------\n\n";
                ignoreLine();
        }
    }
}

//Add value 1 or 11 according to respective choices when ace gets selected
bool aceChoice(const Player& player)
{
    if (player.score() <= g_limit_ace)
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
                    ignoreLine();
                    return true;
                case 'b':
                    ignoreLine();
                    return false;
                default:
                    std::cout << "--------------------------------------\n";
                    std::cout << "Invalid choice! Enter choice again. \n";
                    std::cout << "--------------------------------------\n\n";
                    ignoreLine();
            }
        }
    }

    else
        return true;

}

bool limitDealerAce(const Player& dealer)
{
    return(dealer.score() > g_limit_ace);
}

bool playerTurn(Deck& deck, Player& player)
{
    while (true)
    {
        if(player.isBust())
        {
            std::cout << "You're busted ! \n";
            std::cout << "Your deck: ";
            player.printDeck();
            return true; //Player busted
        }
        else
        {
            if (playerWantsHit())
            {
                int playerCardValue{ player.drawCard(deck, g_player, player) };

                std::cout << '\n';

                std::cout << "You were dealt a " << playerCardValue << '\n';
                std::cout << "Current score: " << player.score() << "\n\n";
            }

            else
            {
                std::cout << "Your deck: ";
                player.printDeck();

                return false; //Player wasn't busted
            }
        }
    }
}

bool dealerTurn(Deck& deck, Player& dealer)
{

    while (dealer.score() < g_minScore)
    {
        sleep(4);
        int dealerCardValue{ dealer.drawCard(deck, g_dealer, dealer) };
        std::cout << '\n';
        std::cout << "Dealer was dealt a " << dealerCardValue << '\n';
        std::cout << "Dealer's current score: " << dealer.score() << "\n\n";
    }

    if(dealer.isBust())
    {
        std::cout << "Dealer busted ! \n";
        std::cout << "Dealer's deck: ";
        dealer.printDeck();
        return true; //Dealer busted
    }

    else
    {
        std::cout << "Dealer's deck: ";
        dealer.printDeck();
        return false;
    }

}

int playGame(Deck& deck)
{

    std::cout << "\n============= Your Turn =============\n\n";
    Player player{};

    bool player_turn{playerTurn(deck, player)};
    std::cout << "Your final score: " << player.score() << "\n\n";

    if (player_turn)
    {
        return 0;
    }

    askEnter();

    std::cout << "\n=========== Dealer's Turn ===========\n\n";
    Player dealer{};

    bool dealer_turn{dealerTurn(deck, dealer)};
    std::cout << "Dealer's final score: " << dealer.score() << "\n\n";

    if (dealer_turn)
    {
        return 1;
    }

    if(player.score() > dealer.score())
        return 1;

    if(player.score() < dealer.score())
        return 0;

    if(player.score() == dealer.score())
        return 2;

    return 3;
}

void executeGame()
{
    Deck deck{};
    deck.shuffle();

    switch (playGame(deck))
    {
        case 0:
            std::cout << "You loose ! \n";
            break;
        case 1:
            std::cout << "You win ! \n";
            break;
        case 2:
            std::cout << "It's a tie ! \n";
            break;
        case 3: //If any case is missing then error will be shown
            std::cerr << "ERROR! Unknown state. \n";
            break;
    }
}

