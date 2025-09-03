#include "StatePlayHand.hpp"
#include "StateCalculateHandPoints.hpp"
#include "Game.hpp"

void StatePlayHand::enter(Game& game){
    std::cout<<"PlayHand enter"<<std::endl;
    if(game.getDeck().cardsLeft()==0)
        game.setIsDrawingAllowed(false);
}

void StatePlayHand::update(Game& game){
    //std::cout<<"Update  "<<(game.getCurrentHand().first ==nullptr ? "nullptr" : game.getCurrentHand().first->toString())<<" "<<(game.getCurrentHand().second ==nullptr ? "nullptr" : game.getCurrentHand().second->toString())<<std::endl;
    if(game.getCurrentHand().first!= nullptr && game.getCurrentHand().second !=nullptr)
    {
        std::cout<<"Changing states to calculate"<<std::endl;
        game.setState(std::make_unique<StateCalculateHandPoints>());
    }
}


