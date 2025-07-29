#ifndef CALCULATEHANDPOINTSSTATE_HPP
#define CALCULATEHANDPOINTSSTATE_HPP

#include "StateGame.hpp"
#include <iostream>

class StateCalculateHandPoints : public StateGame{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif