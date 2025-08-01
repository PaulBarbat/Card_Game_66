
#include "Deck.hpp"

void Deck::addCard(std::shared_ptr<ICard> card){
    m_deck.push_back(std::move(card));
}

std::shared_ptr<ICard> Deck::drawCard(){
    if(m_currentCard >= m_deck.size())
        return nullptr;
    std::cout<<"Current Card is "<<m_deck[m_currentCard]->toString()<<" position "<<m_currentCard <<std::endl;
    return m_deck[m_currentCard++];
}

void Deck::shuffleDeck(){
    std::cout<<"Shuffle the deck"<<std::endl;
    auto randomizer = std::default_random_engine {};
    std::shuffle(std::begin(m_deck), std::end(m_deck), randomizer);
    m_currentCard=0;
}

void Deck::printDeck(){
    std::cout<<"The deck has "<<m_deck.size()<<" Cards"<<std::endl;
    for(std::vector<std::shared_ptr<ICard>>::const_iterator i = m_deck.cbegin(); i!= m_deck.cend(); ++i)    
        std::cout <<(*i)->toString() <<" position "<<std::distance(m_deck.cbegin(), i)<< std::endl;    
    std::cout <<"Tromf is "<<this->getTromf()->toString(); 
}

std::shared_ptr<ICard> Deck::getTromf() const{
    if (m_deck.empty()) return nullptr;
    return m_deck.at(m_deck.size()-1);
}

void Deck::showFirstCard()const{
    std::cout<<m_deck[m_currentCard]->toString()<<" position "<<m_currentCard<<std::endl;
}

uint32_t Deck::cardsLeft() const{
    return m_deck.size()-m_currentCard;
}