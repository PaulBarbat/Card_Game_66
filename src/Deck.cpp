
#include "Deck.hpp"

void Deck::addCard(std::shared_ptr<ICard> card){
    this->deck.push_back(std::move(card));
}

std::shared_ptr<ICard> Deck::drawCard(){
    if(this->currentCard >= this->deck.size())
        return nullptr;
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
    for(std::vector<std::shared_ptr<ICard>>::const_iterator i = this->deck.begin(); i!= this->deck.end(); ++i)
        std::cout <<(*i)->toString() << std::endl;
}