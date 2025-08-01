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

#include <typeinfo>

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
        loadTexture(CardID(rank,suite),path);
        m_deck.addCard(std::make_shared<Card<MagyarSuite,MagyarRank>>(suite,rank,points));
    }
    return std::make_unique<Deck>(m_deck);
}

Game::Game(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font):
    m_context(window, renderer, font),
    m_players(makePlayer("Paul"),makePlayer("Coco")),
    m_deck(makeDeck())
{
    loadTexture(CardID(MagyarRank::Back, MagyarSuite::Back),"resources/cards/back.png");
    loadTexture(CardID(MagyarRank::Placeholder, MagyarSuite::Placeholder),"resources/cards/placeholder.png");
    loadTexture(CardID(MagyarRank::Background, MagyarSuite::Background),"resources/Background.png");
    setState(std::make_unique<StateStart>());
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

void Game::loadTexture(CardID id,const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load surface from " << path << ": " << IMG_GetError() << "\n";
        std::cin.get();
        throw std::runtime_error("Failed to load surface from "+path);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_context.m_renderer.get(), surface);
    SDL_FreeSurface(surface);
   
    if (!texture) {
        std::cerr << "Failed to create texture from " << path << ": " << SDL_GetError() << "\n";
    }
    try {
        m_cardTextures.emplace(id, texture);
    } catch (const std::exception& e) {
        std::cerr << "Caught std::exception of type: " << typeid(e).name() << "\n";
        std::cerr << "What(): " << e.what() << "\n"; 
        std::cin.get();
    } catch (...) {
        std::cerr << "Caught unknown non-std exception!\n"; 
        std::cin.get();
    }
}

bool Game::renderBackground(){
    auto it = m_cardTextures.find(CardID(MagyarRank::Background, MagyarSuite::Background));
    if(it!= m_cardTextures.end()){
        SDL_Texture* texture = it->second;
        SDL_Rect destination{0,0,c_windowWidth, c_windowHeight};
        SDL_RenderCopy(m_context.m_renderer.get(), texture, nullptr, &destination);
        return true;
    }
    else{
        std::cerr << "Missing texture for card!\n";
        std::cin.get();
    }
    return false;
}

bool Game::renderCard(CardID cardID, int x, int y, double rotate){
    auto it = m_cardTextures.find(cardID);
    if(it!= m_cardTextures.end()){
        SDL_Texture* texture = it->second;
        SDL_Rect destination{x,y,c_cardWidth, c_cardHeight};
        SDL_RenderCopyEx(m_context.m_renderer.get(), texture, nullptr, &destination, rotate, nullptr, SDL_FLIP_NONE);
        return true;
    }
    else{
        std::cerr << "Missing texture for card!\n";   
        std::cin.get();
    }
    return false;
}

bool Game::renderText(const std::string& text,int x, int y){
    //std::string cardsLeft=std::to_string(m_deck->cardsLeft());

    int textWidth, textHeight;
    TTF_SizeText(m_context.m_font.get(), text.c_str(), &textWidth, &textHeight);

    SDL_Rect textRect{x-textWidth/2, y-textHeight/2, textWidth, textHeight};

    SDL_Surface* textSurface = TTF_RenderText_Blended(m_context.m_font.get(), text.c_str(), {255, 255, 255});
    if(!textSurface){
        std::cerr<<"Error creating text Surface: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("text surface create error");
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_context.m_renderer.get(), textSurface);
    if(!texture){
        std::cerr<<"Error creating text texture: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("text texture create error");
    }
    SDL_RenderCopy(m_context.m_renderer.get(), texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);
    return true;
}

void Game::render(bool isFirst,Hand& hand){
    SDL_SetRenderDrawColor(m_context.m_renderer.get(), 30, 30, 30, 255);
    SDL_RenderClear(m_context.m_renderer.get());

    renderBackground();
    //render the hand
    int offset=static_cast<int>((c_windowWidth-((hand.size()*c_cardWidth)+((hand.size()-1)*20)))/2);//20px between cards
    for(const auto& card: hand)
    {
        renderCard(card.first->getCardID(), offset, c_windowHeight-c_cardHeight-70, 0.0);
        offset+=c_cardWidth+20;
    }

    int x=(c_windowWidth-c_cardWidth)/2;
    int y=(c_windowHeight-(2*c_cardHeight))-100;
    //render played card
    if(isFirst)
    {
        renderCard(CardID(MagyarRank::Placeholder, MagyarSuite::Placeholder),x,y, 0.0);
    } 
    else{
        renderCard(m_currentHand.first->getCardID(),x,y, 0.0);
    }

    //render tromf
    x+=c_cardWidth+150;
    y-=(c_cardHeight/2)-(c_cardWidth/2)-10;
    renderCard(m_deck->getTromf()->getCardID(),x, y, 90.0 );

    //render deck
    x+=(c_cardWidth/2);
    for(int i=0; i<static_cast<int>(m_deck->cardsLeft()/2); i++)
    {
        renderCard(CardID(MagyarRank::Back, MagyarSuite::Back),x,y, 0.0);
        x+=5;
        y-=5;
    }

    x+=c_cardWidth/2;
    y+=c_cardHeight/2;
    renderText(std::to_string(m_deck->cardsLeft()),x,y);
    SDL_RenderPresent(m_context.m_renderer.get());

    // std::string content = "";
    // if(isFirst){
    //     for(size_t i=0;i<hand.size();i++){
    //         if(hand.at(i).second.empty())
    //             std::cout<<"       "<<std::endl;
    //         else{
    //             content = std::to_string(i+1) + ".";
    //             for(std::vector<CardOption>::const_iterator j = hand.at(i).second.begin()+1; j!= hand.at(i).second.end(); ++j){
    //                 content+=j->shortDescription;
    //                 if(j!=hand.at(i).second.end())
    //                     content+=",";
    //             }
    //         }
    //     }
    // }
    // else
    //     for(size_t i=1;i<=hand.size();i++)
    // if(isFirst){
    //     if(m_deck->cardsLeft()>2)
    //         std::cout<</*hand.size()+2<<". Close the card"<<*/std::endl;
    // }
}
void Game::run() {

    setState(std::make_unique<StateStart>());
    while(m_gameState){
        m_gameState->update(*this);
    }

}
