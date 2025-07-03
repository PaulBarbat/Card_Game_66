#include "PlayHandState.hpp"
#include "CalculateHandPointsState.hpp"
#include "Game.hpp"

void PlayHandState::enter(Game& game){
    if(game.getDeck().cardsLeft()==0)
        game.setIsDrawingAllowed(false);
}

void PlayHandState::update(Game& game){
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
    game.setState(std::make_unique<CalculateHandPointsState>());
}

