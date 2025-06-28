#include "PlayHandState.hpp"
#include "CalculateHandPointsState.hpp"
#include "Game.hpp"

void PlayHandState::enter(Game& game){
    std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<"it is "<<game.getFirstPlayer().getName()<<"'s turn"<<std::endl;
    game.setCurrentHand(game.getFirstPlayer().playHand(game.getDeck()) , game.getSecondPlayer().playHand(game.getDeck()));
}

void PlayHandState::update(Game& game){
    game.setState(std::make_unique<CalculateHandPointsState>());
}

