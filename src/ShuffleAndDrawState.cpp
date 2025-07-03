#include "ShuffleAndDrawState.hpp"
#include "PlayHandState.hpp"
#include "Game.hpp"
#include <random>

void ShuffleAndDrawState::enter(Game& game){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 20);
    for(int i=0;i<=dist(gen);i++)
        game.getDeck().shuffleDeck();
    game.setIsDrawingAllowed(true);
    game.getFirstPlayer().resetPlayerForNewRound();
    game.getSecondPlayer().resetPlayerForNewRound();
}

void ShuffleAndDrawState::update(Game& game){
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

    game.setState(std::make_unique<PlayHandState>());
}

