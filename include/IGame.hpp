#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "ICard.hpp"
#include "Player.hpp"

struct GameContext{
    bool m_isCardClosed;
    bool m_isFirstPlayer;
    size_t m_cardsLeft;
    size_t m_points; //REMOVE
    Hand m_hand;
    CardID m_playedCard;
    CardID m_tromf;
    std::string m_playerName;
    std::vector<CardID> m_currentHand;
    std::unordered_map<CardID,std::vector<OptionType>, CardHash, CardEqual> m_options;
};

class IGame{
public:
    GameContext m_context;
    virtual void update() = 0;
    virtual void playOption(const CardID& id, const OptionType& option) = 0;
    virtual void closeCard() = 0;
    virtual void endRound() = 0;
    virtual void getCurrentPlayerHand() = 0;
};