#ifndef ICARD_HPP
#define ICARD_HPP
#include <string>

class ICard{
    public:
    virtual ~ICard() = default;
    virtual std::string toString() const = 0;
};

#endif