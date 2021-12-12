#include "define.h"

//Initialise constructor Card
Card::Card(Rank rank, Suit suit) : m_rank{ rank }, m_suit{ suit } {}

//Print card code of each card e.g., Jack of Spade is coded as JS
void Card::printCode() const {
    switch(m_rank) {
        case rank_two  :   std::cout << '2';   break;
        case rank_three:   std::cout << '3';   break;
        case rank_four :   std::cout << '4';   break;
        case rank_five :   std::cout << '5';   break;
        case rank_six  :   std::cout << '6';   break;
        case rank_seven:   std::cout << '7';   break;
        case rank_eight:   std::cout << '8';   break;
        case rank_nine :   std::cout << '9';   break;
        case rank_ten  :   std::cout << 'T';   break;
        case rank_jack :   std::cout << 'J';   break;
        case rank_queen:   std::cout << 'Q';   break;
        case rank_king :   std::cout << 'K';   break;
        case rank_ace  :   std::cout << 'A';   break;

        default        :   std::cout << '?';   break;
    }

    switch(m_suit) {
        case suit_clubs    :   std::cout << 'C';   break;
        case suit_diamonds :   std::cout << 'D';   break;
        case suit_hearts   :   std::cout << 'H';   break;
        case suit_spades   :   std::cout << 'S';   break;

        default            :   std::cout << '?';   break;
    }
}

//Get the value of the chosen card according to blackjack rules
int Card::getValue() const {
    switch(m_rank) {
        //Ace could also have value 1 based on player's choice
        case rank_two  :   return 2 ;
        case rank_three:   return 3 ;
        case rank_four :   return 4 ;
        case rank_five :   return 5 ;
        case rank_six  :   return 6 ;
        case rank_seven:   return 7 ;
        case rank_eight:   return 8 ;
        case rank_nine :   return 9 ;
        case rank_ten  :
        case rank_jack :
        case rank_queen:
        case rank_king :   return 10;
        case rank_ace  :   return 11;

        default        :   assert(false && "\nThis should never happen\n");
    }
}

//Create the deck of 52 cards
Deck::Deck() {
    index_t index{ 0 };

    for (int suit{ 0 }; suit < Card::max_suits; ++suit) {
        for (int rank{ 0 }; rank < Card::max_ranks; ++rank) {
            m_deck[index] = {static_cast<Card::Rank>(rank),
                             static_cast<Card::Suit>(suit)};
            ++index;
        }
    }
}

//Shuffle the deck
void Deck::shuffle() {
    //seed is static so it only gets seeded once.
    static std::mt19937 seed{static_cast<std::mt19937::result_type>(std::time(nullptr))};
    std::shuffle(m_deck.begin(), m_deck.end(), seed);
    std::cout << "\n======= Deck has been shuffled ======\n";
}

//To deal a card to the player (not its value)
const Card& Deck::dealCard() {
    assert(m_cardIndex < m_deck.size());
    return m_deck[m_cardIndex++];
}

//To set the type of player (user or dealer)
void Player::setType(char type) {
    m_type = type;
}

//To get the type of player (user or dealer)
char Player::getType() const {
    return m_type;
}

//To put the selected card into the player's own deck
void Player::putCard(Card card) {
    m_deck.push_back(card);
}

//To get the value of the dealt card
int Player::drawCard(Deck& deck, Player& player) {
    Card card{ deck.dealCard() };
    int value = card.getValue();

    if(value == g_ace_11) {
        switch(player.getType()) {
            case g_user  : value = (aceChoice(player)) ? g_ace_1 : g_ace_11;
                           break;
            case g_dealer: value = (limitDealerAce(player)) ? g_ace_1 : g_ace_11;
                           break;

            default    :    assert(false && "\nThis should never happen\n");
        }
    }

    card.printCode();
    player.putCard(card);

    m_score += value;
    return value;
}

//Get player's score
int Player::getScore() const {
    return m_score;
}

//Check whether player is busted
bool Player::isBust() const {
    return (m_score > g_maxScore);
}

//Print the elements in a deck
void Player::printDeck() const {
    for(const Card& card : m_deck) {
        card.printCode();
        std::cout << ' ';
    }
    std::cout << '\n';
}