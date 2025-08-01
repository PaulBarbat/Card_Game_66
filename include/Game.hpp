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

inline constexpr std::size_t c_cardWidth{180};
inline constexpr std::size_t c_cardHeight{290};//these are the sizes of the sprites i use
inline constexpr std::size_t c_windowWidth{1600};
inline constexpr std::size_t c_windowHeight{1000};


struct GameContext{
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_font;

    GameContext()=delete;
    GameContext(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font)
        :   m_window(window, SDL_DestroyWindow),
            m_renderer(renderer, SDL_DestroyRenderer),
            m_font(font, TTF_CloseFont){
                std::cout << "Renderer in GameContextConstructor: " << renderer << std::endl;
            }
    GameContext(const GameContext&) = delete;
    GameContext& operator=(const GameContext&) = delete;
    GameContext(GameContext&&) = delete;
    GameContext& operator=(GameContext&&) = delete;
};

class Game{
public:
    Game(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);
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
    void loadTexture(CardID id,const std::string& path);
    bool renderBackground();
    bool renderCard(CardID cardID, int x, int y, double rotate);
    void render(bool isFirst,Hand& hand);

    void update();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

private:
    std::unordered_map<CardID, SDL_Texture*, CardHash, CardEqual> m_cardTextures;
    GameContext m_context;
    std::pair<std::unique_ptr<Player> ,std::unique_ptr<Player> > m_players;
    std::unique_ptr<Deck> m_deck;
    std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> m_currentHand;

    std::unique_ptr<StateGame> m_gameState;

    //Game rules change if there are no more cards to draw 
    //or if one of the players chooses to "close the cards"
    bool m_isDrawingAllowed;
};

#endif