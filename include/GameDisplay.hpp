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

inline OptionType textureIdToOptionType(const TextureID& id){
    switch(id){
        case TextureID::Button20Play:
            return OptionType::Play20;
        case TextureID::Button20End:
            return OptionType::Play20End;
        case TextureID::Button40Play:
            return OptionType::Play40;
        case TextureID::Button40End:
            return OptionType::Play40End;
        case TextureID::ButtonChangeTromf:
            return OptionType::ChangeTromf;
        case TextureID::ButtonPlay:
            return OptionType::Play;
        default:
            return OptionType::Play;
    }
}

inline TextureID optionTypeToTextureId(const OptionType& option) {
    switch (option) {
        case OptionType::Play20:
            return TextureID::Button20Play;
        case OptionType::Play20End:
            return TextureID::Button20End;
        case OptionType::Play40:
            return TextureID::Button40Play;
        case OptionType::Play40End:
            return TextureID::Button40End;
        case OptionType::ChangeTromf:
            return TextureID::ButtonChangeTromf;
        case OptionType::Play:
            return TextureID::ButtonPlay;
        default:
            return TextureID::Placeholder; // fallback
    }
}

inline std::string textureIdToString(TextureID id) {
    switch (id) {
        case Background:         return "Background";
        case Button20End:        return "Button20End";
        case Button20Play:       return "Button20Play";
        case Button40End:        return "Button40End";
        case Button40Play:       return "Button40Play";
        case ButtonChangeTromf:  return "ButtonChangeTromf";
        case ButtonCloseTheCard: return "ButtonCloseTheCard";
        case ButtonEndTheRound:  return "ButtonEndTheRound";
        case ButtonPlay:         return "ButtonPlay";
        case IconActions:        return "IconActions";
        case IconTromf:          return "IconTromf";
        case CardAcornAce:       return "CardAcornAce";
        case CardAcornKing:      return "CardAcornKing";
        case CardAcornOber:      return "CardAcornOber";
        case CardAcornTen:       return "CardAcornTen";
        case CardAcornUnter:     return "CardAcornUnter";
        case CardBellAce:        return "CardBellAce";
        case CardBellKing:       return "CardBellKing";
        case CardBellOber:       return "CardBellOber";
        case CardBellTen:        return "CardBellTen";
        case CardBellUnter:      return "CardBellUnter";
        case CardHeartAce:       return "CardHeartAce";
        case CardHeartKing:      return "CardHeartKing";
        case CardHeartOber:      return "CardHeartOber";
        case CardHeartTen:       return "CardHeartTen";
        case CardHeartUnter:     return "CardHeartUnter";
        case CardLeafAce:        return "CardLeafAce";
        case CardLeafKing:       return "CardLeafKing";
        case CardLeafOber:       return "CardLeafOber";
        case CardLeafTen:        return "CardLeafTen";
        case CardLeafUnter:      return "CardLeafUnter";
        case Back:               return "Back";
        case Placeholder:        return "Placeholder";
        default:                 return "UnknownTextureID";
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
    bool isClicked = false;

    int h = 0;
    int w = 0;

    LocalizedTexture() = default;
    LocalizedTexture(const Vertex& p, const TextureID& c, float phase = 0.0f, int height = 0, int width = 0)
        : pos(p), id(c), wavePhase(phase) , h(height), w(width) {}
};


class GameDisplay {
private:
    bool m_isCardSelected;
    CardID m_selectedCard;
    std::unordered_map<TextureID, SDL_Texture*> m_textures;
    std::array<LocalizedTexture,5> m_cardPositions;
    std::array<LocalizedTexture,3> m_ButtonPositions;
    LocalizedTexture m_CloseTheCardButton;
    LocalizedTexture m_EndRoundButton;
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
    bool renderClickableOptions();
    void render();
    int handleEvents();
    void handleMouseHover(int x, int y);
    bool handleMouseClick(int x, int y);
    bool pointOnTexture(int x, int y, int cardX, int cardY ,int h, int w);

    void run();
};