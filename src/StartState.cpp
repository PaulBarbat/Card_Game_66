#include "StartState.hpp"
#include "ShuffleAndDrawState.hpp"
#include "Game.hpp"
#include <utility>

void StartState::enter(Game& game){
    std::cout<<"Just entered the starting state"<<std::endl;
}
void StartState::update(Game& game){
    std::cout<<"going to ShuffleAndDraw state"<<std::endl;
    game.setState(std::make_unique<ShuffleAndDrawState>());
}

