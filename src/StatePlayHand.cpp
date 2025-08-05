#include "StatePlayHand.hpp"
#include "StateCalculateHandPoints.hpp"
#include "Game.hpp"

void StatePlayHand::enter(Game& game){
    if(game.getDeck().cardsLeft()==0)
        game.setIsDrawingAllowed(false);
}

void StatePlayHand::update(Game& game){
    // std::cout<<"PlayHand state update"<<std::endl;
    // std::shared_ptr<ICard> first = game.getFirstPlayer().playHand(game.getDeck(),true);
    // if(game.getFirstPlayer().getHasClosedTheCard())
    //     game.setIsDrawingAllowed(false);
    // game.setCurrentHand(first,nullptr);
    // std::shared_ptr<ICard> second;
    // if(game.getIsDrawingAllowed()){
    //     second = game.getSecondPlayer().playHand(game.getDeck(),false);
    // }else{
    //     second = game.getSecondPlayer().playFilteredHand(game.getDeck(),false, first);
    // }
    
    // game.setCurrentHand(first,second);
    std::cout<<"Update  "<<(game.getCurrentHand().first ==nullptr ? "nullptr" : game.getCurrentHand().first->toString())<<" "<<(game.getCurrentHand().second ==nullptr ? "nullptr" : game.getCurrentHand().second->toString())<<std::endl;
    if(game.getCurrentHand().first!= nullptr && game.getCurrentHand().second !=nullptr)
        game.setState(std::make_unique<StateCalculateHandPoints>());
}

void StatePlayHand::render(Game& game){
    //std::cout<<"Render Start"<<std::endl;
    if(game.getCurrentHand().first==nullptr)
        game.render(true,game.getFirstPlayer().getHand());
    else
        game.render(false,game.getSecondPlayer().getHand());
}

bool StatePlayHand::handleEvent(Game& game){
    //std::cout<<"Start Handle Event" <<std::endl;
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        int n = game.handleEvents(e);
        if(n==0)
            return false;
        else if(n==-1)
            return true;
        else if(n>0 && n<=5){
            std::cout<<"We have a winner"<<std::endl;
            if(game.getCurrentHand().first==nullptr)
            {
                std::cout<<"Is first"<<std::endl;
                if(n<=game.getFirstPlayer().getCurrentHandSize())
                {
                    std::cout<<"is a valid option"<<std::endl;
                    game.setCurrentHand(game.getFirstPlayer().getHand().at(n-1).first,nullptr);
                }    
                return true;
            }
            else
            {
                std::cout<<"Is second"<<std::endl;
                if(n<=game.getSecondPlayer().getCurrentHandSize())
                {
                    std::cout<<"is a valid option"<<std::endl;
                    if(game.getIsDrawingAllowed()){
                    std::cout<<"is a valid option"<<std::endl;
                        game.setCurrentHand(game.getCurrentHand().first ,game.getSecondPlayer().getHand().at(n-1).first);
                    }else{
                    std::cout<<"is a valid option"<<std::endl;
                        game.setCurrentHand(game.getCurrentHand().first ,game.getSecondPlayer().getHand().at(n-1).first);
                    }
                }
            }
        }
    }
    return false;
}

