#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>
#include "ICard.hpp"

class Deck {
private:
    uint32_t m_currentCard = 0;
    std::vector<std::shared_ptr<ICard>> m_deck;
public:
    Deck() = default;
    void addCard(std::shared_ptr<ICard> card);
    void shuffleDeck();
    void showFirstCard()const;
    void printDeck();
    std::shared_ptr<ICard> drawCard();
    std::shared_ptr<ICard> getTromf() const;
    uint32_t cardsLeft() const;
};

#endif