#include "PlayHandState.hpp"

void PlayHandState::enter(Game& game){
    game.setCurrentHand(game.getFirstPlayer().playHand(game.getDeck()) , game.getSecondPlayer().playHand(game.getDeck()));
}

void PlayHandState::update(Game& game){
    game.setState(std::make_unique<CalculateHandPointsState>());
}

