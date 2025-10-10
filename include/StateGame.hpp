#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

class Game; 

enum class StateType{
    Start,
    ShuffleAndDraw,
    PlayHand,
    CalculateHandPoints,
    GameOver
};

class StateGame {
public:
    virtual ~StateGame()=default;
    virtual void enter(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual StateType getType() = 0;
};

#endif