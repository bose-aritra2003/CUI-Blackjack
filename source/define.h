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

//Type definitions like enums & structs should be in header file in multi-file programs

enum class Rank
{
    two, three, four, five, six, seven, eight,
    nine, ten, jack, queen, king, ace,

    max_ranks
};

enum class Suit
{
    clubs, diamonds,hearts, spades,

    max_suits
};

struct Card
{
    Rank rank{};
    Suit suit{};
};

struct Player
{
    int score{};
    std::vector<Card> deck{};
};

using deck_t = std::array<Card, 52>;
constexpr int ace_1(1);
constexpr int ace_11(11);
constexpr int limit_ace{40};
constexpr int maxValue{51};
constexpr int minValue{46};

//Forward declarations
void    ignoreLine();
int     getCardValue(const Card& card);
bool    playerWantHit();
bool    playerTurn(const deck_t& deck, Player& player, int& index);
bool    dealerTurn(const deck_t& deck, Player& dealer, int& index);
int     playBlackjack(const deck_t& deck);
void    createDeck(deck_t& deck);
void    shuffleDeck(deck_t& deck);
void    printCard(const Card& card);
void    executeGame(const deck_t& deck);
void    printDeck(const deck_t& deck);
void    printDeck(const std::vector<Card>& deck);

#endif
