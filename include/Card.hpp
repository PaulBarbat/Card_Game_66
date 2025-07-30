#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <stdio.h>
#include "ICard.hpp"
#include "SuiteAndRank.hpp"

template <typename SuiteType, typename RankType>
class Card : public ICard{
private:
    SuiteType m_suite;
    RankType m_rank;
    unsigned m_points;

    template <typename S, typename R>
    friend class Card;
public:
    Card()=delete;

    Card(SuiteType suite, RankType rank, unsigned points): m_suite(suite), m_rank(rank), m_points(points){}

    std::string toString() const override {
        return rankToString(m_rank)+suiteToString(m_suite);
    }

    bool compareSuite(const ICard& card)const{
        auto* other = dynamic_cast<const Card<SuiteType, RankType>*>(&card);
        if (!other) return false; 
        return other->m_suite==m_suite;
    }

    int compareRank(const ICard& card)const{
        auto* other = dynamic_cast<const Card<SuiteType, RankType>*>(&card);
        if(!other) return -2;//to know that there is an Error
        if(other->m_rank==m_rank) return 0;//0 return code means ranks are equal
        else if(other->m_rank < m_rank) return -1;//-1 return code means parameter rank is lower than the current rank
        else return 1;//1 return code means parameter rank is higher than the current rank
    }

    unsigned getEasyRank() const{
        return static_cast<unsigned>(m_rank);
    }

    void changeCard(const ICard& card){
        auto* other = dynamic_cast<const Card<SuiteType, RankType>*>(&card);
        if(!other){
            throw std::invalid_argument("Incompatible card type");
        }
        m_suite = other->m_suite;
        m_rank = other->m_rank;
        m_points = other->m_points;
    }

    std::shared_ptr<ICard> clone() const {
        return std::make_shared<Card<SuiteType, RankType>>(*this);
    }
};

#endif