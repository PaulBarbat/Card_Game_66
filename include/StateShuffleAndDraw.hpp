#ifndef SHUFFLEANDDRAWSTATE_HPP
#define SHUFFLEANDDRAWSTATE_HPP

#include "StateGame.hpp"
#include <iostream>

class StateShuffleAndDraw : public StateGame{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif