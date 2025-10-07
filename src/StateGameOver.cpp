#include "StateGameOver.hpp"
#include "StateShuffleAndDraw.hpp"
#include "Game.hpp"

void StateGameOver::enter(Game& game){
    if(game.m_context.m_isGameOverState==false){
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
        game.m_context.m_isGameOverState=true;
    }
}
void StateGameOver::update(Game& game){
    game.m_context.m_endRoundText.first=game.getFirstPlayer().getName()+" won this round";
    game.m_context.m_endRoundText.second=game.getFirstPlayer().getName()+" "+std::to_string(game.getFirstPlayer().m_roundsWon)+
    " - "+std::to_string(game.getSecondPlayer().m_roundsWon)+" "+game.getSecondPlayer().getName();
    std::cout<<"                                 ROUND OVER"<<std::endl;
    std::cout<<"                                "<<game.getFirstPlayer().getName()<<" won this round"<<std::endl;
    std::cout<<"                             "<<game.getFirstPlayer().getName()<<" "<<game.getFirstPlayer().m_roundsWon<<
    " - "<<game.getSecondPlayer().m_roundsWon<<" "<<game.getSecondPlayer().getName()<<std::endl;
}
