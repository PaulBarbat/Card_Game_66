
#include "Deck.hpp"

void Deck::addCard(std::shared_ptr<ICard> card){
    this->deck.push_back(std::move(card));
}

std::shared_ptr<ICard> Deck::drawCard(){
    if(this->currentCard >= this->deck.size())
        return nullptr;
    std::cout<<"Current Card is "<<currentCard<<std::endl;
    return this->deck[this->currentCard++];
}

void Deck::shuffleDeck(){
    std::cout<<"Shuffle the deck"<<std::endl;
    auto randomizer = std::default_random_engine {};
    std::shuffle(std::begin(this->deck), std::end(this->deck), randomizer);
    this->currentCard=0;
}

void Deck::printDeck(){
    std::cout<<"The deck has "<<this->deck.size()<<" Cards"<<std::endl;
    for(std::vector<std::shared_ptr<ICard>>::const_iterator i = this->deck.cbegin(); i!= this->deck.cend(); ++i)    
        std::cout <<(*i)->toString() <<" position "<<std::distance(this->deck.cbegin(), i)<< std::endl;    
    std::cout <<"Tromf is "<<this->getTromf()->toString(); 
}

std::shared_ptr<ICard> Deck::getTromf() const{
    if (deck.empty()) return nullptr;
    return deck.at(deck.size()-1);
}
