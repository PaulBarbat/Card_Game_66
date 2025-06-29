#include "PlayHandState.hpp"
#include "CalculateHandPointsState.hpp"
#include "Game.hpp"

void PlayHandState::enter(Game& game){
    if(game.getDeck().cardsLeft()==0)
        game.setIsDrawingAllowed(false);
    std::cout<<std::endl<<std::endl<<std::endl;
    std::cout<<"There are "<<game.getDeck().cardsLeft()<<" cards left in the deck"<<std::endl<<std::endl;
}

void PlayHandState::update(Game& game){
    std::shared_ptr<ICard> first = game.getFirstPlayer().playHand(game.getDeck(),true);
    std::shared_ptr<ICard> second;
    if(game.getIsDrawingAllowed()){
        second = game.getSecondPlayer().playHand(game.getDeck(),false);
    }else{
        second = game.getSecondPlayer().playFilteredHand(game.getDeck(),false, first);
    }
    
    game.setCurrentHand(first,second);
    game.setState(std::make_unique<CalculateHandPointsState>());
}

