#ifndef SHUFFLE_H
#define SHUFFLE_H

//All the required libraries, header files, constants, type definitions
// & forward declarations are defined here.

#include "sleep.h"
#include <numeric>
#include <algorithm>
#include <array>
#include <vector>
#include <random>
#include <ctime>
#include <cassert>
#include <iostream>


//All the necessary class definitions and type aliases

constexpr int g_ace_1{1};
constexpr int g_ace_11{11};
constexpr char g_user{'p'}, g_dealer{'d'};
constexpr int g_limit_ace{40};
constexpr int g_maxScore{51};
constexpr int g_minScore{46};

class Player;

class Card
{
public:

    enum Suit
    {
        suit_clubs, suit_diamonds, suit_hearts, suit_spades,

        max_suits
    };

    enum Rank
    {
        rank_two, rank_three, rank_four, rank_five, rank_six, rank_seven, rank_eight,
        rank_nine, rank_ten, rank_jack, rank_queen, rank_king, rank_ace,

        max_ranks
    };

private:
    Rank m_rank{};
    Suit m_suit{};

public:
    Card() = default;
    Card(Rank rank, Suit suit);

    void printCode() const;
    [[nodiscard]]
    int getValue() const;
};

class Deck
{
public:
    using deck_t = std::array<Card, 52>;
    using index_t = deck_t::size_type;

private:
    deck_t m_deck{};
    index_t m_cardIndex{ 0 };

public:
    Deck();
    void shuffle();
    const Card& dealCard();
};


class Player
{
private:
    int m_score{};
    char m_type{};
    std::vector<Card> m_deck{};

public:
    void setType(char type);
    [[nodiscard]]
    char getType() const;
    void putCard(Card card);
    int  drawCard(Deck& deck, Player& dealer);
    [[nodiscard]]
    int  getScore() const;
    [[nodiscard]]
    bool isBust() const;
    void printDeck() const;


};

//Forward declarations

//blackjack.cpp
void ignoreLine();
bool playerWantsHit();
bool aceChoice(const Player& player);
bool limitDealerAce(const Player& dealer);
bool userTurn(Deck& deck, Player& player);
bool dealerTurn(Deck& deck, Player& dealer);
int  playGame(Deck& deck);
void executeGame();

//main.cpp
bool getChoicePlayAgain();
bool getChoiceStartGame();
void displayRules();
void askEnter();

#endif
