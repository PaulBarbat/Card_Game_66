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


Game::Game():
    m_deck(makeDeck()),
    m_players(makePlayer("Paul"),makePlayer("Coco"))
{
    m_context.m_isCardClosed=false;
    m_context.m_isFirstPlayer=true;
    m_context.m_cardsLeft=m_deck->cardsLeft();
    m_context.m_points=0;
    m_context.m_hand=m_players.first->getHand();
    m_context.m_playedCard=CardId(MagyarRank::Placeholder, MagyarSuite::Placeholder);
    m_context.m_tromf=m_deck->getTromf()->getCardId();
    m_context.m_playerName=m_players.first->getName();
    m_context.m_endRoundText=std::pair("","");
    m_players.first->calculateOptions(m_context.m_cardsLeft, m_context.m_tromf,m_context.m_options);
    setState(std::make_unique<StateStart>());
}

void Game::update(){
    m_context.m_tromf=m_deck->getTromf()->getCardId();
    if(m_context.m_cardsLeft!=m_deck->cardsLeft())
        m_context.m_cardsLeft=m_deck->cardsLeft();
    if(m_context.m_isFirstPlayer)
    {
        m_context.m_hand=m_players.first->getHand();
        m_players.first->calculateOptions(m_context.m_cardsLeft, m_context.m_tromf,m_context.m_options);
        m_context.m_points=m_players.first->m_score;
        m_context.m_playerName=m_players.first->getName();
    }
    else{
        m_context.m_hand=m_players.second->getHand();
        m_context.m_points=m_players.second->m_score;
        m_context.m_playerName=m_players.second->getName();
    }
    m_context.m_isGameOverState=m_gameState->getType()==StateType::GameOver;
    if(m_gameState) m_gameState->update(*this);
}

void Game::playOption(const CardId& id, const OptionType& option){
    switch(option){
        case OptionType::Play:
            if(m_context.m_isFirstPlayer){
                m_currentHand.first=m_players.first->getCardById(id);
                m_players.first->removeCard(id);
                m_context.m_isFirstPlayer=false;
                m_context.m_playedCard=id;
            }
            else{
                m_currentHand.second=m_players.second->getCardById(id);
                m_players.second->removeCard(id);
                m_context.m_isFirstPlayer=true;
            }
            break;
        case OptionType::Play20:
            if(m_players.first->m_score==0)
                m_players.first->m_latentPoints+=20;
            else
                m_players.first->m_score+=20;
            m_currentHand.first=m_players.first->getCardById(id);
            if(m_currentHand.first==nullptr)
            {
                throw std::runtime_error("Card is null");
            }
            m_players.first->removeCard(id);
            m_context.m_isFirstPlayer=false;
            m_context.m_playedCard=id;
            m_context.m_hand=m_players.second->getHand();
            break;
        case OptionType::Play20End:
            if(m_players.first->m_score!=0)
                m_players.first->m_score+=20;
            m_currentHand.first=m_players.first->getCardById(id);
            if(m_currentHand.first==nullptr)
            {
                throw std::runtime_error("Card is null");
            }
            endRound();
            break;
        case OptionType::Play40:
            if(m_players.first->m_score==0)
                m_players.first->m_latentPoints+=40;
            else
                m_players.first->m_score+=40;
            m_currentHand.first=m_players.first->getCardById(id);
            if(m_currentHand.first==nullptr)
            {
                throw std::runtime_error("Card is null");
            }
            m_players.first->removeCard(id);
            m_context.m_isFirstPlayer=false;
            m_context.m_playedCard=id;
            m_context.m_hand=m_players.second->getHand();
            break;
        case OptionType::Play40End:
            if(m_players.first->m_score!=0)
                m_players.first->m_score+=40;
            m_currentHand.first=m_players.first->getCardById(id);
            if(m_currentHand.first==nullptr)
            {
                throw std::runtime_error("Card is null");
            }
            endRound();
            break;
        case OptionType::ChangeTromf:
            m_players.first->changeTromf(m_players.first->getCardById(id), *m_deck);
            break;
        default:
            break;
    }
}

void Game::closeCard(){
    m_isDrawingAllowed=false;
    m_context.m_isCardClosed=true;
}

void Game::endRound(){
    setState(std::make_unique<StateGameOver>());
}

void Game::getCurrentPlayerHand(){
    m_context.m_hand.clear();
    if(!m_context.m_isFirstPlayer && (m_context.m_isCardClosed||m_context.m_cardsLeft<2))
    {
        const auto tromf=m_deck->getTromf();
        for(const auto& card:m_players.second->getHand()){
            if(card->compareSuite(*m_currentHand.first))
                m_context.m_hand.push_back(card);
        }
        if(m_context.m_hand.size()==0){
            for(const auto& card:m_players.second->getHand()){
                if(card->compareSuite(*tromf))
                    m_context.m_hand.push_back(card);
            }
            if(m_context.m_hand.size()==0){
                m_context.m_hand=m_players.second->getHand();
            }
        }
    }
    else{
        m_context.m_hand= (m_context.m_isFirstPlayer ? m_players.first->getHand() : m_players.second->getHand());
    }
}

void Game::nextRound(){
    setState(std::make_unique<StateShuffleAndDraw>());
}

void Game::setState(std::unique_ptr<StateGame> newState){
    m_gameState = std::move(newState);
    m_gameState->enter(*this);
}

std::unique_ptr<Player> Game::makePlayer(std::string player){
    size_t option=0;
    PlayerType type;
    while(option>0 && option<3)
    {
        option = 1;
        switch(option){
            case(1):{
                type=PlayerType::Player;
                break;
            };
            case(2):{
                type=PlayerType::NPC;
                break;
            };
            default:{
                break;
            }
        }
    }
    return std::make_unique<Player>(type ,player);
}

void Game::swapPlayerOrder(){
    std::swap(m_players.first,m_players.second);
}

std::unique_ptr<Deck> Game::makeDeck(){
    std::string path="resources/Visual_Cards.xml";
    XMLDocument doc;
    Deck m_deck;
    if(doc.LoadFile(path.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Failed to load XML from file "+path);

    auto* root = doc.FirstChildElement("Deck");
    if(!root)
        throw std::runtime_error("Missing <Deck> Element "+path);
     
    for(auto* card = root->FirstChildElement("Card"); card; card = card->NextSiblingElement("Card")){
        std::string suiteStr = card->FirstChildElement("Suite")->GetText();
        std::string rankStr = card->FirstChildElement("Rank")->GetText();
        std::string path = card->FirstChildElement("Path")->GetText();
        MagyarSuite suite;
        MagyarRank rank;
        unsigned points=0;

        if(suiteStr == "Rosu") suite = MagyarSuite::Rosu;
        else if(suiteStr == "Verde") suite = MagyarSuite::Verde;
        else if(suiteStr == "Ghinda") suite = MagyarSuite::Ghinda;
        else if(suiteStr == "Bata") suite = MagyarSuite::Bata;
        else throw std::runtime_error("Invalid suite: " + suiteStr);

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

        m_deck.addCard(std::make_shared<Card<MagyarSuite,MagyarRank>>(suite,rank,points));
    }
    return std::make_unique<Deck>(m_deck);
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

void Game::resetForNextRound(){
    m_context.m_isCardClosed=false;
    setIsDrawingAllowed(true);
    getFirstPlayer().resetPlayerForNewRound();
    getSecondPlayer().resetPlayerForNewRound();
    flushCurrentHand();
}
