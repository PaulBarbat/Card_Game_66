#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <stdio.h>
#include "ICard.hpp"
#include "SuiteAndRank.hpp"

template <typename SuiteType, typename RankType>
class Card : public ICard{
private:
    SuiteType suite;
    RankType rank;

public:
    Card()=delete;
    Card(SuiteType suite, RankType rank): suite(suite), rank(rank){}
    std::string toString() const override {
        return rankToString(rank)+suiteToString(suite);
    }
};

#endif