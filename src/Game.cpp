#include "Game.hpp"
#include "StartState.hpp"
#include "ShuffleAndDrawState.hpp"
#include "PlayHandState.hpp"
#include "CalculateHandPointsState.hpp"
#include "GameOverState.hpp"

std::unique_ptr<Player> Game::makePlayer(std::string player){
    size_t option=0;
    PlayerType type;
    while(option>0 && option<3)
    {
        std::cout<<"Pick the type of Player "<<player<<std::endl;
        std::cout<<"1. Real Player"<<std::endl<<"2. NPC"<<std::endl;
        std::cin>>option;
        switch(option){
            case(1):{
                type=PlayerType::Player;
                break;
            };
            case(2):{
                type=PlayerType::Player;
                break;
            };
            default:{
                std::cout<<"Not an option"<<std::endl;
            }
        }
    }
    return std::make_unique<Player>(type, [this]() { this->setState(std::make_unique<GameOverState>()); },player);
}

std::unique_ptr<Deck> Game::makeDeck(){
    size_t option=0;
    std::string deckPath="0";
    DeckType type=DeckType::Classic;
    while(option<1 || option>2)
    {
        std::cout<<"Pick the type of Deck you want to play with"<<std::endl;
        std::cout<<"1. Classic Deck"<<std::endl<<"2. Magyar Deck"<<std::endl;
        std::cin>>option;
        switch(option){
            case(1):{
                type=DeckType::Classic;
                deckPath="resources/Clasic_Cards.xml";
                break;
            };
            case(2):{
                type=DeckType::Magyar;
                deckPath="resources/Magyar_Cards.xml";
                break;
            };
            default:{
                std::cout<<"Not an option"<<std::endl;
            }
        }
    }
    return CardFactory::createDeckFromXML(type, deckPath);
}

Game::Game(){
    this->players = {makePlayer("Paul"),makePlayer("Coco")};
    this->deck = makeDeck();
    
    setState(std::make_unique<StartState>());
}

void Game::setState(std::unique_ptr<GameState> newState){
    this->gameState = std::move(newState);
    if(gameState) gameState->enter(*this);
}

void Game::update(){
    if(gameState) gameState->update(*this);
}

void Game::setScore(const std::pair<size_t,size_t>& newScore)
{
    this->score.first=newScore.first;
    this->score.second=newScore.second;
}

void Game::swapPlayerOrder(){
    std::swap(players.first,players.second);
}

std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> Game::getCurrentHand() const{
    return this->currentHand;
}

void Game::setCurrentHand(std::shared_ptr<ICard> first,std::shared_ptr<ICard> second){
    this->currentHand=std::make_pair(first,second);
}

void Game::flushCurrentHand(){
    this->currentHand.first.reset();
    this->currentHand.second.reset();
}


void Game::setIsDrawingAllowed(bool newValue){
    this->isDrawingAllowed=newValue;
}
bool Game::getIsDrawingAllowed(){   
    return this->isDrawingAllowed;
}

void Game::run() {
    // std::cout<<"Creating a Classic Deck"<<std::endl;
    // std::shared_ptr<Deck> classicDeck = CardFactory::createDeckFromXML(DeckType::Classic, "resources/Clasic_Cards.xml");

    
    // std::cout<< std::endl << "Printing the Classic Deck"<<std::endl;
    // classicDeck->printDeck();

    // std::cout<< std::endl << "Shuffling the Classic Deck"<<std::endl;
    // classicDeck->shuffleDeck();

    // std::cout<< std::endl << "Printing the Classic Deck after shuffling"<<std::endl;
    // classicDeck->printDeck();
    
    // std::cout<<"Creating a Magyar Deck"<<std::endl;
    // std::shared_ptr<Deck> magyarDeck = CardFactory::createDeckFromXML(DeckType::Magyar, "resources/Magyar_Cards.xml");
    
    // std::cout<< std::endl << "Printing the Magyar Deck"<<std::endl;
    // magyarDeck->printDeck();

    // std::cout<< std::endl << "Suffling the Magyar Deck"<<std::endl;
    // magyarDeck->shuffleDeck();
    // magyarDeck->shuffleDeck();
    // magyarDeck->shuffleDeck();
    // magyarDeck->shuffleDeck();

    // std::cout<< std::endl << "Printing the Magyar Deck after shuffling"<<std::endl;
    // magyarDeck->printDeck();

    // std::cout<< std::endl << "Creating a Player"<<std::endl;
    // Player p1(PlayerType::Player, [this]() { std::cout<<"ENDING the game"<<std::endl; });
    // Player p2(PlayerType::NPC, [this]() { std::cout<<"ENDING the game"<<std::endl; });
    // std::cout<< std::endl << "Drawing cards"<<std::endl;
    // p1.drawCard(*magyarDeck);
    // p2.drawCard(*magyarDeck);
    // p1.drawCard(*magyarDeck);
    // p2.drawCard(*magyarDeck);
    // p1.drawCard(*magyarDeck);
    // p2.drawCard(*magyarDeck);
    // p1.drawCard(*magyarDeck);
    // p2.drawCard(*magyarDeck);
    // p1.drawCard(*magyarDeck);
    // p2.drawCard(*magyarDeck);

    // std::cout<< std::endl << "Player 1 Showing the hand"<<std::endl;
    // p1.calculateOptions(*magyarDeck);
    // p1.renderOptions();
    // std::cout<< std::endl << "Player 1 Showing the hand"<<std::endl;
    // p2.calculateOptions(*magyarDeck);
    // p2.renderOptions();

    // std::cout<<p1.playCard(1)->toString()<<std::endl;
    // std::cout<<p1.playCard(1)->toString()<<std::endl;

    setState(std::make_unique<StartState>());
    while(gameState){
        gameState->update(*this);
    }

}
