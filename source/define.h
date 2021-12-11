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
constexpr char g_player{'p'}, g_dealer{'d'};
constexpr int g_limit_ace{40};
constexpr int g_maxScore{51};
constexpr int g_minScore{46};

class Player;

class Card
{
public:

    enum Suit
    {
        clubs, diamonds,hearts, spades,

        max_suits
    };

    enum Rank
    {
        two, three, four, five, six, seven, eight,
        nine, ten, jack, queen, king, ace,

        max_ranks
    };

private:
    Rank m_rank{};
    Suit m_suit{};

public:
    Card() = default;
    Card(Rank rank, Suit suit);

    void print() const;
    [[nodiscard]] int value() const;
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

    //Friend functions
    //friend bool playerTurn(Deck& deck, Player& player);
};


class Player
{
private:
    int m_score{};
    std::vector<Card> m_deck{};

public:
    void putCard(Card card);
    int  drawCard(Deck& deck, char player_type, Player& dealer);
    [[nodiscard]] int  score() const;
    [[nodiscard]] bool isBust() const;
    void printDeck() const;


};

//Forward declarations

//blackjack.cpp
void ignoreLine();
bool playerWantsHit();
bool aceChoice(const Player& player);
bool limitDealerAce(const Player& dealer);
bool playerTurn(Deck& deck, Player& player);
bool dealerTurn(Deck& deck, Player& dealer);
int  playGame(Deck& deck);
void executeGame();

//main.cpp
bool getChoicePlayAgain();
bool getChoiceStartGame();
void displayRules();
void askEnter();

#endif
