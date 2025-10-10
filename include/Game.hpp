#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Player.hpp"
#include "StateGame.hpp"
#include "IGame.hpp"

class Game : public IGame{
    friend class StateGameOver;
public:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
    
    void update() override;
    void playOption(const CardId& id, const OptionType& option) override;
    void closeCard() override;
    void endRound() override;
    void getCurrentPlayerHand() override;
    void nextRound() override;
    const GameContext& context() const { return m_context;};

    void setState(std::unique_ptr<StateGame> newState);
    std::unique_ptr<Player> makePlayer(std::string player);
    Player& getFirstPlayer(){ return *m_players.first;}
    Player& getSecondPlayer(){ return *m_players.second;}
    void swapPlayerOrder();
    std::unique_ptr<Deck> makeDeck();
    Deck& getDeck(){ return *m_deck;}

    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> getCurrentHand() const;
    void setCurrentHand(std::shared_ptr<ICard> first,std::shared_ptr<ICard> second);
    void flushCurrentHand();
    void setIsDrawingAllowed(bool newValue);
    bool getIsDrawingAllowed();
    void resetForNextRound();

private:
    bool m_isDrawingAllowed;
    std::unique_ptr<Deck> m_deck;
    std::unique_ptr<StateGame> m_gameState;
    GameContext m_context;
    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> m_currentHand;
    std::pair<std::unique_ptr<Player> ,std::unique_ptr<Player> > m_players;

protected:
    GameContext& getMutableContext() noexcept { return m_context;}
};

#endif