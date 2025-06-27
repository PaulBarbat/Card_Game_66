#ifndef PLAYHANDSTATE_HPP
#define PLAYHANDSTATE_HPP

#include "GameState.hpp"
#include "CalculateHandPointsState.hpp"
#include <iostream>

class PlayHandState : public GameState{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif