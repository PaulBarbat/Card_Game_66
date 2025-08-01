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
    std::vector<std::shared_ptr<ICard>> m_deck;
    uint32_t m_currentCard = 0;
public:
    Deck() = default;
    void addCard(std::shared_ptr<ICard> card);
    std::shared_ptr<ICard> drawCard();
    void shuffleDeck();
    void printDeck();
    std::shared_ptr<ICard> getTromf() const;
    void changeTromf(ICard& card);
    void showFirstCard()const;
    uint32_t cardsLeft() const;
};

#endif