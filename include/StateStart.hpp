#ifndef STARTSTATE_HPP
#define STARTSTATE_HPP

#include "StateGame.hpp"
#include <iostream>

class StateStart : public StateGame{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif