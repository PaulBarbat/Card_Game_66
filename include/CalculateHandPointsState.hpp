#ifndef CALCULATEHANDPOINTSSTATE_HPP
#define CALCULATEHANDPOINTSSTATE_HPP

#include "GameState.hpp"
#include "GameOverState.hpp"
#include "PlayHandState.hpp"
#include <iostream>

class CalculateHandPointsState : public GameState{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif