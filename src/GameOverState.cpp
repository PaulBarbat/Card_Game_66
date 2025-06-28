#include "GameOverState.hpp"
#include "ShuffleAndDrawState.hpp"

void GameOverState::enter(Game& game){
    if(game.getFirstPlayer().getHasClosedTheCard())
        if(game.getFirstPlayer().getScore()>=66)
            game.getFirstPlayer().addRoundsWon(3);
        else
            game.getSecondPlayer().addRoundsWon(3);
    else if(game.getSecondPlayer().getHasClosedTheCard())//if he closed the card but he is the second player, it means he did not win the last round
        game.getFirstPlayer().addRoundsWon(3);
    else if(game.getSecondPlayer().getScore()>=33)
        game.getFirstPlayer().addRoundsWon(1);
    else if(game.getSecondPlayer().getScore()<33)
        game.getFirstPlayer().addRoundsWon(2);
    else if(game.getFirstPlayer().getCurrentHandSize()>0&&game.getFirstPlayer().getScore()>=66)
        if(game.getSecondPlayer().getScore()>=33)
            game.getFirstPlayer().addRoundsWon(1);
        else
            game.getFirstPlayer().addRoundsWon(2);
    else if(game.getFirstPlayer().getCurrentHandSize()>0&&game.getFirstPlayer().getScore()<66)
        if(game.getFirstPlayer().getScore()>=33)
            game.getSecondPlayer().addRoundsWon(1);
        else
            game.getSecondPlayer().addRoundsWon(2);
}
void GameOverState::update(Game& game){
    game.setState(std::make_unique<ShuffleAndDrawState>());
}

