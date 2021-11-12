#include "define.h"

//Whether user wants to ply again or not
bool getChoicePlayAgain()
{
    while (true)
    {
        std::cout << "Do you want to play again (y / n): ";
        char choice{};
        std::cin >> choice;

        switch (choice)
        {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                std::cout << "Invalid choice ! \n";
                std::cout << "--------------------------------------\n";
        }
    }
}

bool getChoiceStartGame()
{
    while (true)
    {
        std::cout << "Do you want to start the game (y / n): ";
        char choice{};
        std::cin >> choice;

        switch (choice)
        {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                std::cout << "Invalid choice ! \n";
                std::cout << "--------------------------------------\n";
        }
    }
}

//To display the welcome note and the rules of the game
void displayRules()
{   std::cout << "\n===== Welcome to BLACKJACK-CUI =====\n"
                 "\n============ Game Rules ============\n"
                 " * There are two contestants, player & dealer.\n"
                 " * The player goes first.\n"
                 " * A player can repeatedly “hit” or “stand”.\n"
                 " * If the player “stands”, their turn is over, and their score is calculated based on the cards they have been dealt.\n"
                 " * If the player “hits”, they get another card and the value of that card is added to their total score.\n"
                 " * All the numbered cards have the value same as their number.\n"
                 " * Jack, Queen & King have value 10 each.\n"
                 " * An ace normally counts as a 1 or an 11 (whichever is better for the total score).\n"
                 " * If the player goes over a score of 51, they bust and lose immediately.\n"
                 " * The dealer goes after the player.\n"
                 " * The dealer repeatedly draws until they reach a score of 46 or more, at which point they stand.\n"
                 " * If the dealer goes over a score of 51, they bust and the player wins immediately.\n"
                 " * Otherwise, if the player has a higher score than the dealer, the player wins.\n"
                 " * Otherwise, the player loses.\n"
                 " * If the player and dealer have the same score (and the player has not gone bust), the result is a tie and neither wins.\n"
                 "\n=====================================\n";

}

//MAIN
int main()
{
    deck_t deck;
    createDeck(deck);
    displayRules();

    if(getChoiceStartGame())
        goto start_here;
    else
    {
        std::cout << "\n===== Thank you, see you again! ====\n ";
        return 0;
    }



    start_here: //In case the player wants to play again/start playing
        std::cout << "\n============ Game Begins ===========\n";
        shuffleDeck(deck);
        executeGame(deck);
        std::cout << "\n=====================================\n";

    if(getChoicePlayAgain())
        goto start_here;
    else
        std::cout << "\n===== Thank you, see you again! ====\n ";
}