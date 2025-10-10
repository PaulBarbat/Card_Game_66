#include "StateGameOver.hpp"
#include "StateShuffleAndDraw.hpp"
#include "Game.hpp"

void StateGameOver::enter(Game& game){
    if(game.context().m_isGameOverState==false){
        int pointsWon=0;
        if(game.context().m_isCardClosed){
            pointsWon=3;
            if(game.getFirstPlayer().m_hasClosedTheCard)
            {
                if(game.getFirstPlayer().m_score<66){
                    game.swapPlayerOrder();
                }
            }
        }
        else if(game.getFirstPlayer().getCurrentHandSize()>0 && game.getFirstPlayer().m_score<66){
                game.swapPlayerOrder();
        }
        if(game.getSecondPlayer().m_score>=33){
            pointsWon=1;
        } 
        else{
            pointsWon=2;
        }
        game.getFirstPlayer().m_roundsWon+=pointsWon;
        game.getMutableContext().m_isGameOverState=true;
    }
}
void StateGameOver::update(Game& game){
    game.getMutableContext().m_endRoundText.first=game.getFirstPlayer().getName()+" won this round";
    game.getMutableContext().m_endRoundText.second=game.getFirstPlayer().getName()+" "+std::to_string(game.getFirstPlayer().m_roundsWon)+
    " - "+std::to_string(game.getSecondPlayer().m_roundsWon)+" "+game.getSecondPlayer().getName();
}
