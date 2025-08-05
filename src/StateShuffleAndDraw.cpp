#include "StateShuffleAndDraw.hpp"
#include "StatePlayHand.hpp"
#include "Game.hpp"
#include <random>

void StateShuffleAndDraw::enter(Game& game){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 20);
    for(int i=0;i<=dist(gen);i++)
        game.getDeck().shuffleDeck();
    game.setIsDrawingAllowed(true);
    game.getFirstPlayer().resetPlayerForNewRound();
    game.getSecondPlayer().resetPlayerForNewRound();
}

void StateShuffleAndDraw::update(Game& game){
    std::cout<<"ShuffleAndDraw state update"<<std::endl;
    game.getFirstPlayer().drawCard(game.getDeck());
    game.getFirstPlayer().drawCard(game.getDeck());
    game.getFirstPlayer().drawCard(game.getDeck());
    game.getFirstPlayer().drawCard(game.getDeck());
    game.getFirstPlayer().drawCard(game.getDeck());
    game.getSecondPlayer().drawCard(game.getDeck());
    game.getSecondPlayer().drawCard(game.getDeck());
    game.getSecondPlayer().drawCard(game.getDeck());
    game.getSecondPlayer().drawCard(game.getDeck());
    game.getSecondPlayer().drawCard(game.getDeck());

    game.setState(std::make_unique<StatePlayHand>());
}

void StateShuffleAndDraw::render(Game& game){
    std::cout<<"Render Shuffle"<<std::endl;
}

bool StateShuffleAndDraw::handleEvent(Game& game){
    std::cout<<"Shuffle Handle Event" <<std::endl;
    return true;
}
