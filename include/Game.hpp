#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Player.hpp"
#include "StateGame.hpp"
#include "IGame.hpp"

class Game : public IGame{
public:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
    
    void update() override;
    void playOption(const CardID& id, const OptionType& option) override;
    void closeCard() override;
    void endRound() override;
    Hand& getCurrentPlayerHand() override;

    void setState(std::unique_ptr<StateGame> newState);
    std::unique_ptr<Player> makePlayer(std::string player);
    std::unique_ptr<Deck> makeDeck();
    Player& getFirstPlayer(){ return *m_players.first;}
    Player& getSecondPlayer(){ return *m_players.second;}
    void swapPlayerOrder();
    Deck& getDeck(){ return *m_deck;}

    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> getCurrentHand() const;
    void setCurrentHand(std::shared_ptr<ICard> first,std::shared_ptr<ICard> second);
    void flushCurrentHand();
    void setIsDrawingAllowed(bool newValue);
    bool getIsDrawingAllowed();

private:
    std::pair<std::unique_ptr<Player> ,std::unique_ptr<Player> > m_players;
    std::unique_ptr<Deck> m_deck;
    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> m_currentHand;

    std::unique_ptr<StateGame> m_gameState;

    //Game rules change if there are no more cards to draw 
    //or if one of the players chooses to "close the cards"
    bool m_isDrawingAllowed;
};

#endif