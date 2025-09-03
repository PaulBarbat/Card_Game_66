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

enum class PlayerType{
    Player,
    NPC
};

using Hand = std::vector<std::shared_ptr<ICard>>;

class Player{
public:
    Player() = delete;
    Player(PlayerType type, std::string name);

    std::string getName() const { return m_name;}
    using Hand = std::vector<std::shared_ptr<ICard>>;
    Hand& getHand() {return m_hand;}
    size_t getCurrentHandSize()const { return m_hand.size();}
    void resetPlayerForNewRound();
    void drawCard(Deck& deck);
    std::shared_ptr<ICard> getCardById(CardID id);
    void removeCard(CardID id);
    void changeTromf(std::shared_ptr<ICard> card, Deck& deck);
    void calculateOptions(int cards_left, const CardID& tromf, std::unordered_map<CardID,std::vector<OptionType>, CardHash, CardEqual> &options);

    //Tromf is the name given to the color that can take any card. 
    //If the player has the Two of Tromf and he starts a turn, 
    //as long as there are more than 2 cards in the deck, he can change it with his Two of Tromf.

    bool m_hasClosedTheCard;
    size_t m_score;
    size_t m_roundsWon;
    size_t m_latentPoints; //Some points can be declared at one point but can only be added whenever the player takes a card.
    
private:
    static constexpr size_t s_MAX_HAND_SIZE = 5;
    PlayerType m_type;
    std::string m_name;
    Hand m_hand;
};

#endif