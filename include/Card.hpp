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
    unsigned points;

    template <typename S, typename R>
    friend class Card;
public:
    Card()=delete;

    Card(SuiteType suite, RankType rank, unsigned points): suite(suite), rank(rank), points(points){}

    std::string toString() const override {
        return rankToString(rank)+suiteToString(suite);
    }

    bool compareSuite(const ICard& card)const{
        auto* other = dynamic_cast<const Card<SuiteType, RankType>*>(&card);
        if (!other) return false; 
        return other->suite==this->suite;
    }

    int compareRank(const ICard& card)const{
        auto* other = dynamic_cast<const Card<SuiteType, RankType>*>(&card);
        if(!other) return -2;//to know that there is an Error
        if(other->rank==this->rank) return 0;//0 return code means ranks are equal
        else if(other->rank < this->rank) return -1;//-1 return code means parameter rank is lower than the current rank
        else return 1;//1 return code means parameter rank is higher than the current rank
    }

    unsigned getEasyRank() const{
        return static_cast<unsigned>(rank);
    }

    void changeCard(const ICard& card){
        auto* other = dynamic_cast<const Card<SuiteType, RankType>*>(&card);
        if(!other){
            throw std::invalid_argument("Incompatible card type");
        }
        this->suite = other->suite;
        this->rank = other->rank;
        this->points = other->points;
    }

    std::shared_ptr<ICard> clone() const {
        return std::make_shared<Card<SuiteType, RankType>>(*this);
    }
};

#endif