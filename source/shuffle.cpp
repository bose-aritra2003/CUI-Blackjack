#include "define.h"

//Create the deck of 52 cards
void createDeck(deck_t& deck)
{
    int index{0};

    for(int suit{0}; (suit < static_cast<int>(Suit::max_suits)); ++suit)
    {
        for(int rank{0}; (rank < static_cast<int>(Rank::max_ranks)); ++rank)
        {
            deck[index].suit = static_cast<Suit>(suit);
            deck[index].rank = static_cast<Rank>(rank);
            ++index;
        }
    }
}

//Shuffle the deck
void shuffleDeck(deck_t& deck)
{
    //seed is static so it only gets seeded once.
    static std::mt19937 seed{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

    std::shuffle(deck.begin(), deck.end(), seed);
    std::cout << "\n======= Deck has been shuffled ======\n";
}

//Print card code of each card e.g., Jack of Spade is coded as JS
void printCard(const Card& card)
{
    switch(card.rank)
    {
        case Rank::two  :   std::cout << '2';   break;
        case Rank::three:   std::cout << '3';   break;
        case Rank::four :   std::cout << '4';   break;
        case Rank::five :   std::cout << '5';   break;
        case Rank::six  :   std::cout << '6';   break;
        case Rank::seven:   std::cout << '7';   break;
        case Rank::eight:   std::cout << '8';   break;
        case Rank::nine :   std::cout << '9';   break;
        case Rank::ten  :   std::cout << 'T';   break;
        case Rank::jack :   std::cout << 'J';   break;
        case Rank::queen:   std::cout << 'Q';   break;
        case Rank::king :   std::cout << 'K';   break;
        case Rank::ace  :   std::cout << 'A';   break;

        default:
            std::cout << '?';
            break;
    }

    switch(card.suit)
    {
        case Suit::clubs    :   std::cout << 'C';   break;
        case Suit::diamonds :   std::cout << 'D';   break;
        case Suit::hearts   :   std::cout << 'H';   break;
        case Suit::spades   :   std::cout << 'S';   break;

        default:
            std::cout << '?';
            break;
    }
}

//Print the elements in the deck
void printDeck(const deck_t& deck)
{
    for(const auto& element : deck)
    {
        printCard(element);
        std::cout << ' ';
    }
    std::cout << '\n';
}

//To print the deck of a player
void printDeck(const std::vector<Card>& deck)
{
    for(const auto& element : deck)
    {
        printCard(element);
        std::cout << ' ';
    }
    std::cout << '\n';
}