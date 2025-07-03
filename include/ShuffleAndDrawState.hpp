#ifndef SHUFFLEANDDRAWSTATE_HPP
#define SHUFFLEANDDRAWSTATE_HPP

#include "GameState.hpp"
#include <iostream>

class ShuffleAndDrawState : public GameState{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif