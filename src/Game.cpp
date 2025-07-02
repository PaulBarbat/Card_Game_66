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
    return std::make_unique<Player>(type, [this]() { this->setState(std::make_unique<GameOverState>()); }, [this](bool isFirst,Hand& hand) { this->render(isFirst,hand); },player);
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
    if(gameState){
        gameState->enter(*this);
        gameState->update(*this);
    } 
}

void Game::update(){
    if(gameState) gameState->update(*this);
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

void Game::render(bool isFirst,Hand& hand){
    int tromfCounter=0;
    int playedCardCounter=0;
    std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
    std::cout<<isFirst<<std::endl;
    if(isFirst)
    {
        std::cout<<getFirstPlayer().getName()<<"                                                     Over All Score"<<std::endl;
        std::cout<<"Points: "<<getFirstPlayer().getScore()<<"                                             "<<getFirstPlayer().getName()<<" "<<getFirstPlayer().getRoundsWon()<<" : "<<getSecondPlayer().getRoundsWon()<<" "<<getSecondPlayer().getName()<<std::endl<<std::endl;
    } 
    else{
        std::cout<<getSecondPlayer().getName()<<"                                                     Over All Score"<<std::endl;
        std::cout<<"Points: "<<getSecondPlayer().getScore()<<"                                             "<<getFirstPlayer().getName()<<" "<<getFirstPlayer().getRoundsWon()<<" : "<<getSecondPlayer().getRoundsWon()<<" "<<getSecondPlayer().getName()<<std::endl<<std::endl;
    }
    std::cout<<"                                                          Deck: "<<getDeck().cardsLeft()<<" Cards Left"<<std::endl;
    std::cout<<"                                                                Tromf"<<std::endl;
    std::cout<<"                                                           "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "Play a card": "Played Card")<<"            "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                                           "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<std::endl;
    std::cout<<std::endl<<std::endl<<std::endl;
    //This implementation right now is made for card representations that are 12 rows deep
    for(int i=0; i<12;i++)
    {
        for(const auto& card : hand)
        {
            std::cout<<card.first->toString(i)<<" ";
        }
        std::cout<<std::endl;
    }
    std::string content = "";
    int padding = 0;
    if(isFirst){
        for(int i=0;i<hand.size();i++){
            if(hand.at(i).second.empty())
                std::cout<<"       "<<i+1<<"         ";
            else{
                content = std::to_string(i+1) + ".";
                for(std::vector<CardOption>::const_iterator j = hand.at(i).second.begin()+1; j!= hand.at(i).second.end(); ++j){
                    content+=j->shortDescription;
                    if(j!=hand.at(i).second.end())
                        content+=",";
                }
                padding = (16 - content.size())/2;
                std::cout<<std::string(padding, ' ')<<content<<std::string(padding, ' ');
            }
        }
        std::cout<<std::endl<<"Other Options"<<std::endl;
    }
    else
        for(int i=1;i<=hand.size();i++)
            std::cout<<"       "<<i<<"         ";
    if(isFirst){
        std::cout<<hand.size()+1<<". That is enough for me(close the round)"<<std::endl;
        if(isDrawingAllowed)
            std::cout<<hand.size()+2<<". Close the card"<<std::endl;
    }
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
