#include "StateStart.hpp"
#include "StateShuffleAndDraw.hpp"
#include "Game.hpp"
#include <utility>

void StateStart::enter(Game& /*game*/){
    std::cout<<"Just entered the starting state"<<std::endl;
}

void StateStart::update(Game& game){
    std::cout<<"going to ShuffleAndDraw state"<<std::endl;
    game.setState(std::make_unique<StateShuffleAndDraw>());
}

void StateStart::render(Game& game){
    std::cout<<"Render Start"<<std::endl;
}

bool StateStart::handleEvent(Game& game){
    std::cout<<"Start Handle Event" <<std::endl;
    return true;
}

