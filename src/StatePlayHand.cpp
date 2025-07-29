#include "StatePlayHand.hpp"
#include "StateCalculateHandPoints.hpp"
#include "Game.hpp"

void StatePlayHand::enter(Game& game){
    if(game.getDeck().cardsLeft()==0)
        game.setIsDrawingAllowed(false);
}

void StatePlayHand::update(Game& game){
    std::shared_ptr<ICard> first = game.getFirstPlayer().playHand(game.getDeck(),true);
    if(game.getFirstPlayer().getHasClosedTheCard())
        game.setIsDrawingAllowed(false);
    game.setCurrentHand(first,nullptr);
    std::shared_ptr<ICard> second;
    if(game.getIsDrawingAllowed()){
        second = game.getSecondPlayer().playHand(game.getDeck(),false);
    }else{
        second = game.getSecondPlayer().playFilteredHand(game.getDeck(),false, first);
    }
    
    game.setCurrentHand(first,second);
    game.setState(std::make_unique<StateCalculateHandPoints>());
}

