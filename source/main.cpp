#include "define.h"

//Whether user wants to play again or not
bool getChoicePlayAgain() {
    while (true) {
        std::cout << "Do you want to play again (y / n): ";
        char choice{};
        std::cin >> choice;

        switch (choice) {
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

//Ask the user whether to start the game or not
bool getChoiceStartGame() {
    while (true) {
        ignoreLine();
        std::cout << "Do you want to start the game (y / n): ";
        char choice{};
        std::cin >> choice;

        switch (choice) {
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

//To display the welcome note, developer info, rules of the game & reference legend
void displayRules() {
    std::cout << "\n===== Welcome to BLACKJACK-CUI =====\n"
                 "\nProject by Aritra Bose,\n"
                 "Undergraduate Information Technology student,\n"
                 "Indian Institute of Engineering Science & Technology, Shibpur\n"
                 "West Bengal, India.\n"
                 "\n============ Game Rules ============\n\n"
                 " * There are two contestants, player & dealer.\n"
                 " * The player goes first.\n"
                 " * A player can repeatedly “hit” or “stand”.\n"
                 " * If the player “stands”, their turn is over, and their score is calculated based on the cards they have been dealt.\n"
                 " * If the player “hits”, they get another card and the value of that card is added to their total score.\n"
                 " * All the numbered cards have the value same as their number.\n"
                 " * Jack, Queen & King have value 10 each.\n"
                 " * An ace normally counts as a 1 or an 11 (based on player's choice unless his/her total score is greater than 40).\n"
                 " * If the player goes over a score of 51, they bust and lose immediately.\n"
                 " * The dealer goes after the player.\n"
                 " * The dealer repeatedly draws cards until they reach a score of 46 or more, at which point they stand.\n"
                 " * If the dealer goes over a score of 51, they bust and the player wins immediately.\n"
                 " * Otherwise, if the player has a higher score than the dealer, the player wins, vice versa the player loses.\n"
                 " * If the player and dealer have the same score (and the player has not gone bust), the result is a tie and neither wins.\n"
                 "\n============= Legend ===============\n\n"
                 " * A - Ace        T - Ten        J - Jack        Q - Queen        K - King\n"
                 " * C - Clubs      D - Diamonds   H - Hearts      S - Spades\n"
                 "\n====================================\n";
}

//Ask the user to press enter key to continue
void askEnter() {
    std::cout << "\nPress ENTER key to continue...";
    std::cin.get();
}

//MAIN
int main() {
    displayRules();

    askEnter();

    if(getChoiceStartGame())
        goto start_here;
    else {
        std::cout << "\n===== Thank you, see you again! =====\n ";
        return 0;
    }

    start_here: //In case the player wants to play again/start playing
        std::cout << "\n============ Game Begins ============\n";
        executeGame();
        std::cout << "\n=====================================\n";

    if(getChoicePlayAgain())
        goto start_here;
    else
        std::cout << "\n===== Thank you, see you again! ====\n ";
}
