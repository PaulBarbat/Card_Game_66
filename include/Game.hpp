#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <unordered_map>
#include "Player.hpp"
#include "StateGame.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using CardID = std::pair<MagyarRank, MagyarSuite>;

struct GameContext{
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_font;

    GameContext(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font)
        :   m_window(window, SDL_DestroyWindow),
            m_renderer(renderer, SDL_DestroyRenderer),
            m_font(font, TTF_CloseFont){}
};

class Game{
public:
    Game();
    GameContext createContext();
    void setState(std::unique_ptr<StateGame> newState);
    void run();

    Player& getFirstPlayer(){ return *m_players.first;}
    Player& getSecondPlayer(){ return *m_players.second;}
    void swapPlayerOrder();
    Deck& getDeck(){ return *m_deck;}

    std::unique_ptr<Player> makePlayer(std::string player);
    std::unique_ptr<Deck> makeDeck();
    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> getCurrentHand() const;
    void setCurrentHand(std::shared_ptr<ICard> first,std::shared_ptr<ICard> second);
    void flushCurrentHand();
    void setIsDrawingAllowed(bool newValue);
    bool getIsDrawingAllowed();
    void render(bool isFirst,Hand& hand);

    void update();

private:
    std::pair<std::unique_ptr<Player> ,std::unique_ptr<Player> > m_players;
    std::unique_ptr<Deck> m_deck;
    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> m_currentHand;
    GameContext m_context;
    std::unordered_map<CardID, SDL_Texture*, CardHash, CardEqual> cardTextures;

    std::unique_ptr<StateGame> m_gameState;

    //Game rules change if there are no more cards to draw 
    //or if one of the players chooses to "close the cards"
    bool m_isDrawingAllowed;
};

#endif