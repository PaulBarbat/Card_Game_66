#pragma once
#include "IGame.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>

inline constexpr std::size_t c_cardWidth{180};
inline constexpr std::size_t c_cardHeight{290};//these are the sizes of the sprites i use
inline constexpr std::size_t c_windowWidth{1600};
inline constexpr std::size_t c_windowHeight{1000};

enum TextureID{
    Background,
    Button20End,
    Button20Play,
    Button40End,
    Button40Play,
    ButtonChangeTromf,
    ButtonCloseTheCard,
    ButtonEndTheRound,
    ButtonPlay,
    IconActions,
    IconTromf,
    CardAcornAce,
    CardAcornKing,
    CardAcornOber,
    CardAcornTen,
    CardAcornUnter,
    CardBellAce,
    CardBellKing,
    CardBellOber,
    CardBellTen,
    CardBellUnter,
    CardHeartAce,
    CardHeartKing,
    CardHeartOber,
    CardHeartTen,
    CardHeartUnter,
    CardLeafAce,
    CardLeafKing,
    CardLeafOber,
    CardLeafTen,
    CardLeafUnter,
    Back,
    Placeholder
};

inline TextureID cardIdToTextureId(const CardID& id){
    switch(id.second){
        case MagyarSuite::Ghinda:
            switch(id.first){
                case MagyarRank::Doi:
                    return TextureID::CardAcornUnter;
                    break;
                case MagyarRank::Trei:
                    return TextureID::CardAcornOber;
                    break;
                case MagyarRank::Cal:
                    return TextureID::CardAcornKing;
                    break;
                case MagyarRank::Craita:
                    return TextureID::CardAcornTen;
                    break;
                case MagyarRank::Tuz:
                    return TextureID::CardAcornAce;
                    break;
                default:
                    return TextureID::Placeholder;
                    break;
            }
            break;
        case MagyarSuite::Bata:
            switch(id.first){
                case MagyarRank::Doi:
                    return TextureID::CardBellUnter;
                    break;
                case MagyarRank::Trei:
                    return TextureID::CardBellOber;
                    break;
                case MagyarRank::Cal:
                    return TextureID::CardBellKing;
                    break;
                case MagyarRank::Craita:
                    return TextureID::CardBellTen;
                    break;
                case MagyarRank::Tuz:
                    return TextureID::CardBellAce;
                    break;
                default:
                    return TextureID::Placeholder;
                    break;
            }
            break;
        case MagyarSuite::Rosu:
            switch(id.first){
                case MagyarRank::Doi:
                    return TextureID::CardHeartUnter;
                    break;
                case MagyarRank::Trei:
                    return TextureID::CardHeartOber;
                    break;
                case MagyarRank::Cal:
                    return TextureID::CardHeartKing;
                    break;
                case MagyarRank::Craita:
                    return TextureID::CardHeartTen;
                    break;
                case MagyarRank::Tuz:
                    return TextureID::CardHeartAce;
                    break;
                default:
                    return TextureID::Placeholder;
                    break;
            }
            break;
        case MagyarSuite::Verde:
            switch(id.first){
                case MagyarRank::Doi:
                    return TextureID::CardLeafUnter;
                    break;
                case MagyarRank::Trei:
                    return TextureID::CardLeafOber;
                    break;
                case MagyarRank::Cal:
                    return TextureID::CardLeafKing;
                    break;
                case MagyarRank::Craita:
                    return TextureID::CardLeafTen;
                    break;
                case MagyarRank::Tuz:
                    return TextureID::CardLeafAce;
                    break;
                default:
                    return TextureID::Placeholder;
                    break;
            }
            break;
        default:
                return TextureID::Placeholder;
                break;
    }
}

inline CardID textureIdToCardId(const TextureID& id){
    switch(id){
        case TextureID::CardAcornUnter:
            return CardID(MagyarRank::Doi, MagyarSuite::Ghinda);
        case TextureID::CardAcornOber:
            return CardID(MagyarRank::Trei, MagyarSuite::Ghinda);
        case TextureID::CardAcornKing:
            return CardID(MagyarRank::Cal, MagyarSuite::Ghinda);
        case TextureID::CardAcornTen:
            return CardID(MagyarRank::Craita, MagyarSuite::Ghinda);
        case TextureID::CardAcornAce:
            return CardID(MagyarRank::Tuz, MagyarSuite::Ghinda);
        case TextureID::CardBellUnter:
            return CardID(MagyarRank::Doi, MagyarSuite::Bata);
        case TextureID::CardBellOber:
            return CardID(MagyarRank::Trei, MagyarSuite::Bata);
        case TextureID::CardBellKing:
            return CardID(MagyarRank::Cal, MagyarSuite::Bata);
        case TextureID::CardBellTen:
            return CardID(MagyarRank::Craita, MagyarSuite::Bata);
        case TextureID::CardBellAce:
            return CardID(MagyarRank::Tuz, MagyarSuite::Bata);
        case TextureID::CardHeartUnter:
            return CardID(MagyarRank::Doi, MagyarSuite::Rosu);
        case TextureID::CardHeartOber:
            return CardID(MagyarRank::Trei, MagyarSuite::Rosu);
        case TextureID::CardHeartKing:
            return CardID(MagyarRank::Cal, MagyarSuite::Rosu);
        case TextureID::CardHeartTen:
            return CardID(MagyarRank::Craita, MagyarSuite::Rosu);
        case TextureID::CardHeartAce:
            return CardID(MagyarRank::Tuz, MagyarSuite::Rosu);
        case TextureID::CardLeafUnter:
            return CardID(MagyarRank::Doi, MagyarSuite::Verde);
        case TextureID::CardLeafOber:
            return CardID(MagyarRank::Trei, MagyarSuite::Verde);
        case TextureID::CardLeafKing:
            return CardID(MagyarRank::Cal, MagyarSuite::Verde);
        case TextureID::CardLeafTen:
            return CardID(MagyarRank::Craita, MagyarSuite::Verde);
        case TextureID::CardLeafAce:
            return CardID(MagyarRank::Tuz, MagyarSuite::Verde);
        default:
            return CardID(MagyarRank::Placeholder, MagyarSuite::Placeholder);
    }
}

using Vertex = std::pair<int, int>;
struct LocalizedTexture {
    Vertex pos;       // base position
    TextureID id;        // card type

    // Wave animation
    float waveOffsetY = 0.0f;
    float wavePhase = 0.0f;   // for phase difference between cards

    // Hover animation
    float scale = 1.0f;       // 1.0 = normal, >1.0 = highlighted
    bool isHovered = false;

    LocalizedTexture() = default;
    LocalizedTexture(const Vertex& p, const TextureID& c, float phase = 0.0f)
        : pos(p), id(c), wavePhase(phase) {}
};


class GameDisplay {
private:
    std::unordered_map<TextureID, SDL_Texture*> m_textures;
    std::array<LocalizedTexture,5> m_cardPositions;
    size_t m_handSize = 0;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    std::unique_ptr<IGame> m_game;
public:
    GameDisplay();
    ~GameDisplay();
    GameDisplay(const GameDisplay& ) = delete;
    GameDisplay& operator=(const GameDisplay&) = delete;
    GameDisplay(GameDisplay&&) = delete;
    GameDisplay& operator=(GameDisplay&&) = delete;

    void loadTextures(const std::string& path);
    void loadSingleTexture(TextureID id, const std::string& path);
    bool renderBackground();
    bool renderCard(TextureID cardID, int x, int y, double rotate,float scale = 1.0f);
    bool renderTexture(TextureID id, int h, int w, int x, int y, double rotate, float scale);
    bool renderText(const std::string& text,int x, int y);
    bool renderOptions(TextureID id,int x, int y);
    void render();
    int handleEvents();
    void handleMouseHover(int x, int y);
    bool handleMouseClick(int x, int y);
    bool pointOnCardInHand(int x, int y, int cardX, int cardY);

    void run();
};