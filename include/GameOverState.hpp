#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "GameState.hpp"
#include "Game.hpp"
#include <iostream>

class GameOverState : public GameState{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

#endif