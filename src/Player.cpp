#include "Player.hpp"

Player::Player(PlayerType type, std::function<void()> endGameCallback) : type(type), endGameCallback(endGameCallback), score(0) {}

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
                        [this](){if(this->score>0)
                                this->addScore(40);
                            else
                               this->latentPoints+=40;
                            }
                    });
                    i->second.push_back({
                        "Call 40 and end the round",
                        [this](){
                            if(this->score>0)
                                this->addScore(40);
                            else
                               this->latentPoints+=40;
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
                        [this](){
                            if(this->score>0)
                                this->addScore(20);
                            else
                               this->latentPoints+=20;
                            }
                    });
                    i->second.push_back({
                        "Call 20 and end the round",
                        [this](){
                            if(this->score>0)
                                this->addScore(20);
                            else
                               this->latentPoints+=20;
                            this->endRound();
                        }
                    });
                }
            }
    }
}

void Player::renderOptions()const{
    std::cout<<"Here are yout options:"<<std::endl;
    for(Hand::const_iterator i = this->hand.begin(); i!= this->hand.end(); ++i)
    {
        std::cout<<i->first->toString()<<std::endl;
        if(i->second.empty())
            std::cout<<" with no special options"<<std::endl;
        else{
            for(std::vector<CardOption>::const_iterator j = i->second.begin(); j!= i->second.end(); ++j)
                std::cout<<"  - "<<j->description<<std::endl;
        }
    }
}

void Player::drawCard(Deck& deck){
    auto card = deck.drawCard();
    if(card){
        hand.push_back(std::make_pair(card, std::vector<CardOption>{}));
        //hand.push_back({card, {}});
    }
}

std::shared_ptr<ICard> Player::playCard(const unsigned& cardPosition){
    auto& cardEntry = hand.at(cardPosition);
    auto card = cardEntry.first->clone();
    if(cardEntry.second.empty()){
        hand.erase(hand.begin() + cardPosition);
        return card;
    }
    else{
        for(std::vector<CardOption>::iterator i = cardEntry.second.begin(); i!= cardEntry.second.end(); ++i)
            std::cout<<std::distance(cardEntry.second.begin(),i)+1<<" "<<i->description<<std::endl;
        size_t option=0;
        while(true)
        {
            std::cin>>option;
            if(option>0 && option<=cardEntry.second.size()){
                cardEntry.second.at(option-1).action();
                break;
            }
            else{
                std::cout<<"Not an option, try again"<<std::endl;
            }
        }
        hand.erase(hand.begin() + cardPosition);
        return card;
    }    
}
//TODO
void Player::endRound(){
    std::cout<<"END GAME HERE"<<std::endl;
    endGameCallback();
}

void Player::addScore(const unsigned &points)
{
    this->score+=points;
}

void Player::changeTromf(std::shared_ptr<ICard> card, Deck& deck){
    auto copy=deck.getTromf();

    if(!copy || !card)
        return;
        
    auto handCopy = card->clone();
    card->changeCard(*copy);
    copy->changeCard(*handCopy);
}
