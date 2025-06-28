#include "ShuffleAndDrawState.hpp"
#include "PlayHandState.hpp"
#include <random>

void ShuffleAndDrawState::enter(Game& game){
    game.getDeck().shuffleDeck();
    game.getDeck().shuffleDeck();
    game.getDeck().shuffleDeck();
    game.getDeck().shuffleDeck();
    game.getDeck().shuffleDeck();
    game.setIsDrawingAllowed(true);
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

