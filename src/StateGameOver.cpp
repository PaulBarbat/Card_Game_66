#include "StateGameOver.hpp"
#include "StateShuffleAndDraw.hpp"
#include "Game.hpp"

void StateGameOver::enter(Game& game){
    std::cout<<"GAME OVER STATE"<<std::endl;
    std::cout<<game.getFirstPlayer().getName()<<" "<<game.getFirstPlayer().m_score<<" - "<<game.getSecondPlayer().getName()<<" "<<game.getSecondPlayer().m_score<<std::endl;
    std::cout<<game.getFirstPlayer().m_score<<" "<<game.getSecondPlayer().m_score<<std::endl;
    int pointsWon=0;
    if(game.m_context.m_isCardClosed){
        pointsWon=3;
        if(game.getFirstPlayer().m_hasClosedTheCard)
        {
            if(game.getFirstPlayer().m_score<66){
                game.swapPlayerOrder();
                std::cout<<"Case 1"<<std::endl;
            }
        }
    }
    else if(game.getFirstPlayer().getCurrentHandSize()>0 && game.getFirstPlayer().m_score<66){
            game.swapPlayerOrder();
    }
    if(game.getSecondPlayer().m_score>=33){
        pointsWon=1;
        std::cout<<"Case 5"<<std::endl;
    } 
    else{
        pointsWon=2;
        std::cout<<"Case 6"<<std::endl;
    }
    game.getFirstPlayer().m_roundsWon+=pointsWon;
}
void StateGameOver::update(Game& game){
    std::cout<<"                                 ROUND OVER"<<std::endl;
    std::cout<<"                                "<<game.getFirstPlayer().getName()<<" won this round"<<std::endl;
    std::cout<<"                             "<<game.getFirstPlayer().getName()<<" "<<game.getFirstPlayer().m_roundsWon<<
        " - "<<game.getSecondPlayer().m_roundsWon<<" "<<game.getSecondPlayer().getName()<<std::endl;
    game.setState(std::make_unique<StateShuffleAndDraw>());
}
