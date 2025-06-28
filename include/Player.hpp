#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <utility>
#include <memory>
#include <functional>
#include "Deck.hpp"
#include "SuiteAndRank.hpp"


enum class PlayerType{
    Player,
    NPC
};

struct CardOption {
    std::string shortDescription;
    std::string description;//Description of the option. Something like "Play the card as part of 20"
    std::function<void(unsigned position)> action;//Optional. This can be set with a function for example for 2 of Tromf to change it with the Tromf that is down on the deck
};

using Hand = std::vector<std::pair<std::shared_ptr<ICard>,std::vector<CardOption>>>;

class Player{
private:
    PlayerType type;
    unsigned score;
    unsigned roundsWon;
    unsigned latentPoints; //Some points can be declared at one point but can only be added whenever the player takes a card.
    Hand hand;
    static constexpr size_t MAX_HAND_SIZE = 5;
    std::function<void()> endGameCallback;
    bool hasClosedTheCard;
    std::string name;
public:
    Player() = delete;
    Player(PlayerType type,std::function<void()> endGameCallback, std::string name);
    std::shared_ptr<ICard> playHand(Deck& deck, bool isFirst);
    void calculateOptions(Deck& deck);
    void renderOptions() const;
    void drawCard(Deck& deck);
    std::shared_ptr<ICard> playCard(const unsigned& cardPosition);
    void endRound();
    void addScore(const unsigned &points);
    unsigned getScore()const;
    void addRoundsWon(const unsigned &points);
    unsigned getRoundsWon()const;
    void resetPlayerForNewRound();
    //Tromf is the name given to the color that can take any card. 
    //If the player has the Two of Tromf and he starts a turn, 
    //as long as there are more than 2 cards in the deck, he can change it with his Two of Tromf.
    void changeTromf(std::shared_ptr<ICard> card, Deck& deck);
    size_t getCurrentHandSize()const;
    bool getHasClosedTheCard()const;
    std::string getName() const;
};

#endif