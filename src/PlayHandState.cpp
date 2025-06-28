#include "PlayHandState.hpp"
#include "CalculateHandPointsState.hpp"
#include "Game.hpp"

void PlayHandState::enter(Game& game){
    std::cout<<std::endl<<std::endl<<std::endl;
    std::cout<<"There are "<<game.getDeck().cardsLeft()<<" cards left in the deck"<<std::endl<<std::endl;
}

void PlayHandState::update(Game& game){
    std::cout<<"Tromf is "<<game.getDeck().getTromf()->toString()<<std::endl;
    std::cout<<"it is "<<game.getFirstPlayer().getName()<<"'s turn"<<std::endl;
    std::shared_ptr<ICard> first = game.getFirstPlayer().playHand(game.getDeck(),true);

    std::cout<<"Tromf is "<<game.getDeck().getTromf()->toString()<<std::endl;
    std::cout<<"it is "<<game.getSecondPlayer().getName()<<"'s turn"<<std::endl;
    std::shared_ptr<ICard> second = game.getSecondPlayer().playHand(game.getDeck(),false);
    
    game.setCurrentHand(first,second);
    game.setState(std::make_unique<CalculateHandPointsState>());
}

