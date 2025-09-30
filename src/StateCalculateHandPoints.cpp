#include "StateCalculateHandPoints.hpp"
#include "StateGameOver.hpp"
#include "StatePlayHand.hpp"
#include "Game.hpp"

void StateCalculateHandPoints::enter(Game& game){//there probably is a better way to do this
    std::cout<<"Calculate Enter" <<std::endl;
    int compareRank = game.getCurrentHand().first->compareRank(*game.getCurrentHand().second);
    if(compareRank==-2) {
        std::cout<<"There is an error when comparing ranks "<<compareRank<<std::endl;
        return;
    }

    if((game.getCurrentHand().first->compareSuite(*game.getCurrentHand().second) &&//Cards of the same suite
            compareRank==-1) ||//first biger than second 
        (!game.getCurrentHand().first->compareSuite(*game.getCurrentHand().second) &&//Cards of different Suite 
            (game.getCurrentHand().first->compareSuite(*game.getDeck().getTromf()) || //First card is tromf
                (!game.getCurrentHand().second->compareSuite(*game.getDeck().getTromf())))))//second card is not tromf
    {
        std::cout<<game.getFirstPlayer().getName()<<" takes this hand"<<std::endl;
    }
    else{
        std::cout<<game.getSecondPlayer().getName()<<" takes this hand"<<std::endl;
        game.swapPlayerOrder();//Second player will be the first next turn
    }
    game.getFirstPlayer().m_score+=(game.getCurrentHand().first->getEasyRank()+game.getCurrentHand().second->getEasyRank());
    if(game.getFirstPlayer().m_latentPoints>0)
    {
        game.getFirstPlayer().m_score+=game.getFirstPlayer().m_latentPoints;
        game.getFirstPlayer().m_latentPoints=0;
    }
    game.flushCurrentHand();
}

void StateCalculateHandPoints::update(Game& game){
    std::cout<<"Calculate Update" <<std::endl;
    if(game.getIsDrawingAllowed()){
        game.getFirstPlayer().drawCard(game.getDeck());
        game.getSecondPlayer().drawCard(game.getDeck());
    }
    if(game.getDeck().cardsLeft()==0)
        game.setIsDrawingAllowed(false);
    if(game.getFirstPlayer().getCurrentHandSize()==0)
    {
        game.setState(std::make_unique<StateGameOver>());
    }    
    else
        game.setState(std::make_unique<StatePlayHand>());
}
