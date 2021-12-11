#include "define.h"

//Initialise constructor Card
Card::Card(Rank rank, Suit suit) : m_rank{ rank }, m_suit{ suit } {}

//Print card code of each card e.g., Jack of Spade is coded as JS
void Card::print() const
{
    switch(m_rank)
    {
        case two  :   std::cout << '2';   break;
        case three:   std::cout << '3';   break;
        case four :   std::cout << '4';   break;
        case five :   std::cout << '5';   break;
        case six  :   std::cout << '6';   break;
        case seven:   std::cout << '7';   break;
        case eight:   std::cout << '8';   break;
        case nine :   std::cout << '9';   break;
        case ten  :   std::cout << 'T';   break;
        case jack :   std::cout << 'J';   break;
        case queen:   std::cout << 'Q';   break;
        case king :   std::cout << 'K';   break;
        case ace  :   std::cout << 'A';   break;

        default:
            std::cout << '?';
            break;
    }

    switch(m_suit)
    {
        case clubs    :   std::cout << 'C';   break;
        case diamonds :   std::cout << 'D';   break;
        case hearts   :   std::cout << 'H';   break;
        case spades   :   std::cout << 'S';   break;

        default:
            std::cout << '?';
            break;
    }
}

//Get the value of the chosen card according to blackjack rules
int Card::value() const
{
    switch(m_rank)
    {   //Ace could also have value 1 based on player's choice
        case two  :   return 2 ;
        case three:   return 3 ;
        case four :   return 4 ;
        case five :   return 5 ;
        case six  :   return 6 ;
        case seven:   return 7 ;
        case eight:   return 8 ;
        case nine :   return 9 ;
        case ten  :
        case jack :
        case queen:
        case king :   return 10;
        case ace  :   return 11;

        default   :   assert(false && "\nThis should never happen\n");
    }
}

//Create the deck of 52 cards
Deck::Deck()
{
    index_t index{ 0 };

    for (int suit{ 0 }; suit < Card::max_suits; ++suit)
    {
        for (int rank{ 0 }; rank < Card::max_ranks; ++rank)
        {
            m_deck[index] = {static_cast<Card::Rank>(rank),
                             static_cast<Card::Suit>(suit)};
            ++index;
        }
    }
}

//Shuffle the deck
void Deck::shuffle()
{
    //seed is static so it only gets seeded once.
    static std::mt19937 seed{static_cast<std::mt19937::result_type>(std::time(nullptr))};

    std::shuffle(m_deck.begin(), m_deck.end(), seed);
    std::cout << "\n======= Deck has been shuffled ======\n";
}

//To deal a card to the player (not its value)
const Card& Deck::dealCard()
{
    assert(m_cardIndex < m_deck.size());

    return m_deck[m_cardIndex++];
}

void Player::putCard(Card card)
{
    m_deck.push_back(card);
}

int Player::drawCard(Deck& deck, char player_type, Player& player)
{
    Card card{ deck.dealCard() };
    int value = card.value();

    if(value == g_ace_11)
    {
        switch(player_type)
        {
            case g_player: value = (aceChoice(player)) ? g_ace_1 : g_ace_11;
                           break;
            case g_dealer: value = (limitDealerAce(player)) ? g_ace_1 : g_ace_11;
                           break;

            default    :    assert(false && "\nThis should never happen\n");
        }
    }

    card.print();
    player.putCard(card);

    m_score += value;
    return value;
}



int Player::score() const
{
    return m_score;
}

bool Player::isBust() const
{
    return (m_score > g_maxScore);
}

//Print the elements in the deck
void Player::printDeck() const
{
    for(const Card& card : m_deck)
    {
        card.print();
        std::cout << ' ';
    }
    std::cout << '\n';
}

