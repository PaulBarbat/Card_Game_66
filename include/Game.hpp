#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "CardFactory.hpp"
#include "Player.hpp"
#include "GameState.hpp"

class Game{
public:
    Game();
    void setState(std::unique_ptr<GameState> newState);
    void run();

    Player& getFirstPlayer(){ return *players.first;}
    Player& getSecondPlayer(){ return *players.second;}
    void swapPlayerOrder();
    Deck& getDeck(){ return *deck;}

    std::unique_ptr<Player> makePlayer(std::string player);
    std::unique_ptr<Deck> makeDeck();
    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> getCurrentHand() const;
    void setCurrentHand(std::shared_ptr<ICard> first,std::shared_ptr<ICard> second);
    void flushCurrentHand();
    void setIsDrawingAllowed(bool newValue);
    bool getIsDrawingAllowed();

    void update();

private:
    std::pair<std::unique_ptr<Player> ,std::unique_ptr<Player> > players;
    std::unique_ptr<Deck> deck;
    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> currentHand;

    std::unique_ptr<GameState> gameState;

    //Game rules change if there are no more cards to draw 
    //or if one of the players chooses to "close the cards"
    bool isDrawingAllowed;
};

#endif