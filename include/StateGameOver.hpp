#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "StateGame.hpp"
#include <iostream>

class StateGameOver : public StateGame{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
    StateType getType() override {return StateType::GameOver;}
};

#endif