#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "Deck.hpp"
#include "SuiteAndRank.hpp"


enum class PlayerType{
    Player,
    NPC
};

struct CardOption {
    std::string description;//Description of the option. Something like "Play the card as part of 20"
    std::function<void()> action;//Optional. This can be set with a function for example for 2 of Tromf to change it with the Tromf that is down on the deck
};

using Hand = std::map<std::shared_ptr<ICard>,std::vector<CardOption>>;

class Player{
private:
    PlayerType type;
    unsigned score;
    unsigned latentPoints; //Some points can be declared at one point but can only be added whenever the player takes a card.
    Hand hand;
    static constexpr size_t MAX_HAND_SIZE = 5;
public:
    Player() = delete;
    Player(PlayerType type);
    void calculateOptions(Deck& deck);
    void renderOptions();
    void drawCard(Deck& deck);
    void playCard();
    void endRound();
    void addScore(const unsigned &points);
    //Tromf is the name given to the color that can take any card. 
    //If the player has the Two of Tromf and he starts a turn, 
    //as long as there are more than 2 cards in the deck, he can change it with his Two of Tromf.
    void changeTromf(std::shared_ptr<ICard> card, Deck& deck);
    void showHand()const;
};

#endif