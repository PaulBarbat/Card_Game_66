#include "StateStart.hpp"
#include "StateShuffleAndDraw.hpp"
#include "Game.hpp"
#include <utility>

void StateStart::enter(Game& /*game*/){
}

void StateStart::update(Game& game){
    game.setState(std::make_unique<StateShuffleAndDraw>());
}

