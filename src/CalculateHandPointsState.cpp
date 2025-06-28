#include "CalculateHandPointsState.hpp"
#include "GameOverState.hpp"
#include "PlayHandState.hpp"
#include "Game.hpp"

void CalculateHandPointsState::enter(Game& game){//there probably is a better way to do this
    int compareRank = game.getCurrentHand().first->compareRank(*game.getCurrentHand().second);
    if(compareRank!=1 && compareRank!=-1) {
        std::cout<<"There is an error when comparing ranks "<<compareRank<<std::endl;
        return;
    }

    if((game.getCurrentHand().first->compareSuite(*game.getCurrentHand().second) &&//Cards of the same suite
            compareRank==-1) ||//first biger than second 
        (!game.getCurrentHand().first->compareSuite(*game.getCurrentHand().second) &&//Cards of different Suite 
            (game.getCurrentHand().first->compareSuite(*game.getDeck().getTromf()) || //First card is tromf
                (!game.getCurrentHand().second->compareSuite(*game.getDeck().getTromf()) &&//second card is not tromf
                compareRank==-1))))//First biger than second
    {
        std::cout<<game.getFirstPlayer().getName()<<" takes this hand"<<std::endl;
    }
    else{
        std::cout<<game.getSecondPlayer().getName()<<" takes this hand"<<std::endl;
        game.swapPlayerOrder();//Second player will be the first next turn
    }
    game.getFirstPlayer().addScore(game.getCurrentHand().first->getEasyRank()+game.getCurrentHand().second->getEasyRank());
    game.flushCurrentHand();
}

void CalculateHandPointsState::update(Game& game){
    if(game.getDeck().cardsLeft()==0)
        game.setIsDrawingAllowed(false);
    if(game.getIsDrawingAllowed()){
        game.getFirstPlayer().drawCard(game.getDeck());
        game.getSecondPlayer().drawCard(game.getDeck());
    }
    if(game.getFirstPlayer().getCurrentHandSize()==0)
        game.setState(std::make_unique<GameOverState>());
    else
        game.setState(std::make_unique<PlayHandState>());
}

