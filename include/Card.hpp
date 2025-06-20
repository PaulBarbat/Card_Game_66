#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <stdio.h>
#include "ICard.hpp"
#include "SuitAndRank.hpp"

template <typename SuitType, typename RankType>
class Card : public ICard{
private:
    SuitType suit;
    RankType rank;

public:
    Card()=delete;
    Card(SuitType suit, RankType rank): suit(suit), rank(rank){}
    std::string toString() const override {
        return rankToString(rank)+suitToString(suit);
    }
};

#endif