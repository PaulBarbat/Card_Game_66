#ifndef PLAYHANDSTATE_HPP
#define PLAYHANDSTATE_HPP

#include "StateGame.hpp"
#include <iostream>

class StatePlayHand : public StateGame{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif