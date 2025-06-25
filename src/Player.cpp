#include "Player.hpp"

Player::Player(PlayerType type) : type(type), score(0) {}

void Player::calculateOptions(Deck& deck){
    for(Hand::iterator i = this->hand.begin(); i!= this->hand.end(); ++i){
        if(i->first->compareSuite(*deck.getTromf())) 
        {
            if(i->first->getEasyRank()==2){
                i->second.push_back({
                "Change with the Tromf card "+(*deck.getTromf()).toString(),
                [this,&deck, card = i->first](){this->changeTromf(card,deck);}
                });
            }
            else if(i->first->getEasyRank()==3 || i->first->getEasyRank()==4)   
            for(Hand::const_iterator j = this->hand.begin(); j!= this->hand.end(); ++j){
                if(i->first->compareSuite(*j->first) //if cards are of the same Suite
                && i->first->getEasyRank() != j->first->getEasyRank()// and ranks are different (first card is 3 or 4)
                && (j->first->getEasyRank()==3||j->first->getEasyRank()==4))// and second card is 3 or 4
                {
                    i->second.push_back({
                        "Call 40",
                        [this](){this->addScore(40);}
                    });
                    i->second.push_back({
                        "Call 40 and end the round",
                        [this](){
                            this->addScore(40);
                            this->endRound();
                        }
                    });
                }
            }
        } 
        else if(i->first->getEasyRank()==3 || i->first->getEasyRank()==4)   
            for(Hand::const_iterator j = this->hand.begin(); j!= this->hand.end(); ++j){
                if(i->first->compareSuite(*j->first) //if cards are of the same Suite
                && i->first->getEasyRank() != j->first->getEasyRank()// and ranks are different (first card is 3 or 4)
                && (j->first->getEasyRank()==3||j->first->getEasyRank()==4))// and second card is 3 or 4
                {
                    i->second.push_back({
                        "Call 20",
                        [this](){this->addScore(20);}
                    });
                    i->second.push_back({
                        "Call 20 and end the round",
                        [this](){
                            this->addScore(20);
                            this->endRound();
                        }
                    });
                }
            }
    }
}

void Player::renderOptions(){
    std::cout<<"Here are yout options:"<<std::endl;
    for(Hand::const_iterator i = this->hand.begin(); i!= this->hand.end(); ++i)
    {
    }
}

void Player::drawCard(Deck& deck){
    auto card = deck.drawCard();
    if(card){
        hand[card] = std::vector<CardOption>();
    }
}

void Player::playCard(){

}

void Player::endRound(){

}

void Player::addScore(const unsigned &points)
{
    this->score+=points;
}

void Player::changeTromf(std::shared_ptr<ICard> card, Deck& deck){
    auto copy=deck.getTromf();

    if(!copy || !card)
        return;
        
    auto handCopy = *card;
    card->changeCard(*copy);
    copy->changeCard(handCopy);
}

void Player::showHand() const{
    for(Hand::const_iterator i = this->hand.begin(); i!= this->hand.end(); ++i)
    {
        std::cout<<i->first->toString();
        if(i->second.empty())
            std::cout<<" with no special options"<<std::endl;
        else{
            for(std::vector<CardOption>::const_iterator j = i->second.begin(); j!= i->second.end(); ++j)
                std::cout<<"  - "<<j->description<<std::endl;
        }
    }
}