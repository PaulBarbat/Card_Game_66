#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

class Game; //Forward declaration to be able to use it

class StateGame {
public:
    virtual ~StateGame()=default;
    virtual void enter(Game& game) = 0;
    virtual void update(Game& game) = 0;
};

#endif