#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <stdio.h>

enum class Suit{
Hearts = 1,
Diamonds,
Clubs,
Spades
};

enum class Rank{
    Two = 2,
    Three,
    Four,
    Ten = 10,
    Ace
};

class Card{
private:
    Suit suit;
    Rank rank;

public:
    Card()=delete;
    Card(Suit suit, Rank rank);
    std::string toString();
};

#endif