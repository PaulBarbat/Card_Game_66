#ifndef STARTSTATE_HPP
#define STARTSTATE_HPP

#include "GameState.hpp"
#include "ShuffleAndDrawState.hpp"
#include <iostream>

class StartState : public GameState{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif