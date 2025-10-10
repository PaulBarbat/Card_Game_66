#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <utility>
#include <memory>
#include <functional>
#include "Deck.hpp"
#include "SuiteAndRank.hpp"


enum class OptionType{
    Play,
    Play20,
    Play40,
    Play20End,
    Play40End,
    ChangeTromf
};

inline std::string toString(OptionType option) {
    switch (option) {
        case OptionType::Play:        return "Play";
        case OptionType::Play20:      return "Play20";
        case OptionType::Play40:      return "Play40";
        case OptionType::Play20End:   return "Play20End";
        case OptionType::Play40End:   return "Play40End";
        case OptionType::ChangeTromf: return "ChangeTromf";
        default:                      return "UnknownOptionType";
    }
}

enum class PlayerType{
    Player,
    NPC
};

using Hand = std::vector<std::shared_ptr<ICard>>;

class Player{
public:
    Player() = delete;
    Player(PlayerType type, std::string name);

    void resetPlayerForNewRound();
    void removeCard(CardId id);
    void changeTromf(std::shared_ptr<ICard> card, Deck& deck);
    void calculateOptions(int cards_left, const CardId& tromf, std::unordered_map<CardId,std::vector<OptionType>, CardHash, CardEqual> &options);
    void drawCard(Deck& deck);

    std::shared_ptr<ICard> getCardById(CardId id);
    std::string getName() const { return m_name;}
    Hand& getHand() {return m_hand;}
    size_t getCurrentHandSize()const { return m_hand.size();}
    bool m_hasClosedTheCard;
    size_t m_score;
    size_t m_roundsWon;
    size_t m_latentPoints; 
    static constexpr size_t s_MAX_HAND_SIZE = 5;
    PlayerType m_type;
    std::string m_name;
    Hand m_hand;
};

#endif