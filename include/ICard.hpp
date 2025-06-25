#ifndef ICARD_HPP
#define ICARD_HPP
#include <string>

class ICard{
    public:
    virtual ~ICard() = default;
    virtual std::string toString() const = 0;
    virtual bool compareSuite(const ICard& card)const = 0;
    virtual int compareRank(const ICard& card) const = 0;
    virtual unsigned getEasyRank() const = 0;//gets the Rank as an unsigned int for easy decision making, like knowing if the card is a two
    virtual void changeCard(const ICard& card) = 0;
};

#endif