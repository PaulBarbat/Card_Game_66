#include "Game.hpp"
#include "StateStart.hpp"
#include "StateShuffleAndDraw.hpp"
#include "StatePlayHand.hpp"
#include "StateCalculateHandPoints.hpp"
#include "StateGameOver.hpp"
#include "Deck.hpp"
#include "Card.hpp"
#include "SuiteAndRank.hpp"
#include "tinyxml2.h"

using namespace tinyxml2;

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
    return std::make_unique<Player>(type, [this]() { this->setState(std::make_unique<StateGameOver>()); }, [this](bool isFirst,Hand& hand) { this->render(isFirst,hand); },player);
}

std::unique_ptr<Deck> Game::makeDeck(){
    std::string path="resources/Visual_Cards.xml";
    XMLDocument doc;
    Deck m_deck;
    if(doc.LoadFile(path.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Failed to load XML from file "+path);

    //Getting the root of the Deck
    auto* root = doc.FirstChildElement("Deck");
    if(!root)
        throw std::runtime_error("Missing <Deck> Element "+path);
     
    //Getting all elements in Deck
    for(auto* card = root->FirstChildElement("Card"); card; card = card->NextSiblingElement("Card")){
        std::string suiteStr = card->FirstChildElement("Suite")->GetText();
        std::string rankStr = card->FirstChildElement("Rank")->GetText();
        std::string path = card->FirstChildElement("Path")->GetText();
        MagyarSuite suite;
        MagyarRank rank;
        unsigned points=0;

        //get the suite
        if(suiteStr == "Rosu") suite = MagyarSuite::Rosu;
        else if(suiteStr == "Verde") suite = MagyarSuite::Verde;
        else if(suiteStr == "Ghinda") suite = MagyarSuite::Ghinda;
        else if(suiteStr == "Bata") suite = MagyarSuite::Bata;
        else throw std::runtime_error("Invalid suite: " + suiteStr);

        //get the rank
        if(rankStr == "Doi"){
            rank = MagyarRank::Doi;
            points=2;
        } 
        else if(rankStr == "Trei"){
            rank = MagyarRank::Trei;
            points=3;
        } 
        else if(rankStr == "Cal"){
            rank = MagyarRank::Cal;
            points=4;
        } 
        else if(rankStr == "Craita"){
            rank = MagyarRank::Craita;
            points=10;
        } 
        else if(rankStr == "Tuz"){
            rank = MagyarRank::Tuz;
            points=11;
        } 
        else throw std::runtime_error("Invalid rank: " + rankStr);

        //add the card to the m_deck
        m_deck.addCard(std::make_shared<Card<MagyarSuite,MagyarRank>>(suite,rank,points));
    }
    return std::make_unique<Deck>(m_deck);
}

Game::Game():
    m_players(makePlayer("Paul"),makePlayer("Coco")),
    m_deck(makeDeck()),
    m_context(createContext())
{
    setState(std::make_unique<StateStart>());
}

GameContext Game::createContext(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr<<"SDL_Init Error: "<<SDL_GetError() << std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    if(!(IMG_Init(IMG_INIT_PNG)&& IMG_INIT_PNG))
    {
        std::cerr<<"IMG_Init Error: "<<IMG_GetError() << std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    if(TTF_Init() != 0)
    {
        std::cerr<<"TTF Error: "<<TTF_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    SDL_Window* window = SDL_CreateWindow(
        "Card Game 66",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1200,
        800,
        SDL_WINDOW_SHOWN
    );

    if(!window){
        std::cerr<<"SDL Window Creation Error: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("SDL Window Creation Error");
    } 

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!renderer)
    {
        std::cerr<<"Renderer Creation Error: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("Renderer Creation Error");
    }

    TTF_Font* font = TTF_OpenFont("resources/dejavu-fonts-ttf-2.37/ttf/DejaVuSans.ttf", 24);

    if(!font)
    {
        std::cerr<<"Font Opening Error: "<<TTF_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("Font Opening Error");
    }
}

void Game::setState(std::unique_ptr<StateGame> newState){
    m_gameState = std::move(newState);
    if(m_gameState){
        m_gameState->enter(*this);
        m_gameState->update(*this);
    } 
}

void Game::update(){
    if(m_gameState) m_gameState->update(*this);
}

void Game::swapPlayerOrder(){
    std::swap(m_players.first,m_players.second);
}

std::pair<std::shared_ptr<ICard>,std::shared_ptr<ICard>> Game::getCurrentHand() const{
    return m_currentHand;
}

void Game::setCurrentHand(std::shared_ptr<ICard> first,std::shared_ptr<ICard> second){
    m_currentHand=std::make_pair(first,second);
}

void Game::flushCurrentHand(){
    m_currentHand.first.reset();
    m_currentHand.second.reset();
}


void Game::setIsDrawingAllowed(bool newValue){
    m_isDrawingAllowed=newValue;
}
bool Game::getIsDrawingAllowed(){   
    return m_isDrawingAllowed;
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
    std::cout<<"                                                           "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "Play a card": "Played Card")<<"            "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                                           "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
    std::cout<<"                                    "<<(isFirst ? "                ": getCurrentHand().first->toString(playedCardCounter++))<<"       "<<m_deck->getTromf()->toString(tromfCounter++)<<std::endl;
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
        for(size_t i=0;i<hand.size();i++){
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
        for(size_t i=1;i<=hand.size();i++)
            std::cout<<"       "<<i<<"         ";
    if(isFirst){
        std::cout<<hand.size()+1<<". That is enough for me(close the round)"<<std::endl;
        if(m_deck->cardsLeft()>2)
            std::cout<<hand.size()+2<<". Close the card"<<std::endl;
    }
}
void Game::run() {

    setState(std::make_unique<StateStart>());
    while(m_gameState){
        m_gameState->update(*this);
    }

}
