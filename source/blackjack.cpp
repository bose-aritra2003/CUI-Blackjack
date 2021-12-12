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
//unless player's score is greater than 40
bool aceChoice(const Player& user)
{
    if (user.getScore() <= g_limit_ace)
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

//To stop the dealer from choosing 11 value of Ace
//when their score exceeds 40
bool limitDealerAce(const Player& dealer)
{
    return(dealer.getScore() > g_limit_ace);
}

//Let the player pick cards unless he/she stands or busted
bool userTurn(Deck& deck, Player& user)
{
    while (true)
    {
        if(user.isBust())
        {
            std::cout << "You're busted ! \n";
            std::cout << "Your deck: ";
            user.printDeck();
            return true; //Player busted
        }
        else
        {
            if (playerWantsHit())
            {
                int userCardValue{ user.drawCard(deck, user) };

                std::cout << '\n';

                std::cout << "You were dealt a " << userCardValue << '\n';
                std::cout << "Current score: " << user.getScore() << "\n\n";
            }

            else
            {
                std::cout << "Your deck: ";
                user.printDeck();

                return false; //Player wasn't busted
            }
        }
    }
}

//Dealer picks cards from the deck unless busted or stopped
bool dealerTurn(Deck& deck, Player& dealer)
{

    while (dealer.getScore() < g_minScore)
    {
        sleep(4);
        int dealerCardValue{ dealer.drawCard(deck, dealer) };
        std::cout << '\n';
        std::cout << "Dealer was dealt a " << dealerCardValue << '\n';
        std::cout << "Dealer's current score: " << dealer.getScore() << "\n\n";
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

//Initialise player & dealer and start playing
int playGame(Deck& deck)
{

    std::cout << "\n============= Your Turn =============\n\n";
    Player user{};
    user.setType(g_user);

    bool user_turn{userTurn(deck, user)};
    std::cout << "Your final score: " << user.getScore() << "\n\n";

    if (user_turn)
    {
        return 0;
    }

    askEnter();

    std::cout << "\n=========== Dealer's Turn ===========\n\n";
    Player dealer{};
    dealer.setType(g_dealer);

    bool dealer_turn{dealerTurn(deck, dealer)};
    std::cout << "Dealer's final score: " << dealer.getScore() << "\n\n";

    if (dealer_turn)
    {
        return 1;
    }

    if(user.getScore() > dealer.getScore())
        return 1;

    if(user.getScore() < dealer.getScore())
        return 0;

    if(user.getScore() == dealer.getScore())
        return 2;

    return 3;
}

//Execute playGame function to know who wins, losses or ties
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

