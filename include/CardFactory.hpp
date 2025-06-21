#ifndef CARDFACTORY_HPP
#define CARDFACTORY_HPP

#include "Deck.hpp"
#include "Card.hpp"
#include "SuitAndRank.hpp"
#include "tinyxml2.h"


enum class DeckType {
    Classic,
    Magyar
};

class CardFactory{
private:
    static std::shared_ptr<Deck> createClassicDeckFromXML(const std::string& path);
    static std::shared_ptr<Deck> createMagyarDeckFromXML(const std::string& path);
public:
    static std::shared_ptr<Deck> createDeckFromXML(DeckType type, const std::string& path);
};

#endif