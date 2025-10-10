#include "StatePlayHand.hpp"
#include "StateCalculateHandPoints.hpp"
#include "Game.hpp"

void StatePlayHand::enter(Game& game){
    if(game.getDeck().cardsLeft()==0)
        game.setIsDrawingAllowed(false);
}

void StatePlayHand::update(Game& game){
    if(game.getCurrentHand().first!= nullptr && game.getCurrentHand().second !=nullptr)
    {
        game.setState(std::make_unique<StateCalculateHandPoints>());
    }
}


