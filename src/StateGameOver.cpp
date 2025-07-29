#include "StateGameOver.hpp"
#include "StateShuffleAndDraw.hpp"
#include "Game.hpp"

void StateGameOver::enter(Game& game){
    std::cout<<"GAME OVER STATE"<<std::endl;
    int pointsWon=0;
    if(game.getFirstPlayer().getHasClosedTheCard()&&game.getFirstPlayer().getScore()<66){
        game.swapPlayerOrder();
        pointsWon=3;
    }
    else if(game.getSecondPlayer().getHasClosedTheCard())//if he closed the card but he is the second player, it means he did not win the last round
        pointsWon=3;
    else if(game.getSecondPlayer().getScore()>=33)
        pointsWon=1;
    else if(game.getSecondPlayer().getScore()<33)
        pointsWon=2;
    else if(game.getFirstPlayer().getCurrentHandSize()>0&&game.getFirstPlayer().getScore()>=66)
        if(game.getSecondPlayer().getScore()>=33)
            pointsWon=1;
        else
            pointsWon=2;
    else if(game.getFirstPlayer().getCurrentHandSize()>0&&game.getFirstPlayer().getScore()<66)    {
        if(game.getFirstPlayer().getScore()>=33)
            pointsWon=1;
        else
            pointsWon=2;
        game.swapPlayerOrder();
    }
    game.getFirstPlayer().addRoundsWon(pointsWon);
}
void StateGameOver::update(Game& game){
    std::cout<<"                                 ROUND OVER"<<std::endl;
    std::cout<<"                                "<<game.getFirstPlayer().getName()<<" won this round"<<std::endl;
    std::cout<<"                             "<<game.getFirstPlayer().getName()<<" "<<game.getFirstPlayer().getRoundsWon()<<
        " - "<<game.getSecondPlayer().getRoundsWon()<<" "<<game.getSecondPlayer().getName()<<std::endl;
    std::cin.get();
    game.setState(std::make_unique<StateShuffleAndDraw>());
}

