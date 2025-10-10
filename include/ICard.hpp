#ifndef ICARD_HPP
#define ICARD_HPP
#include <string>
#include <memory>
#include "SuiteAndRank.hpp"

using CardId = std::pair<MagyarRank, MagyarSuite>;

class ICard{
    public:
    virtual ~ICard() = default;
    virtual std::shared_ptr<ICard> clone() const = 0;
    virtual CardId getCardId() const = 0;
    virtual bool compareSuite(const ICard& card)const = 0;
    virtual int compareRank(const ICard& card) const = 0;
    virtual unsigned getEasyRank() const = 0;
    virtual void changeCard(const ICard& card) = 0;
    virtual std::string toString() const = 0;
};

#endif