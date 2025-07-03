#include "Player.hpp"

Player::Player(PlayerType type, std::function<void()> endGameCallback, std::function<void(bool isFirst,Hand& hand)> renderCallback, std::string name) 
    : type(type), 
    score(0), 
    roundsWon(0),
    latentPoints(0), 
    hand{},
    endGameCallback(endGameCallback),
    renderCallback(renderCallback), 
    hasClosedTheCard(false),
    name(name) {}

std::shared_ptr<ICard> Player::playHand(Deck& deck, bool isFirst){
    // std::cout<<"Tromf is "<<deck.getTromf()->toString()<<std::endl;
    // std::cout<<"it is "<<this->name<<"'s turn"<<std::endl<<std::endl;
    for(Hand::iterator i = this->hand.begin(); i!= this->hand.end(); ++i)
        i->second.clear();
    if(isFirst)
        this->calculateOptions(deck);
    // this->renderOptions(this->hand);
    // if(isFirst)    {
    //     std::cout<<hand.size()+1<<" That is enough for me(close the round)"<<std::endl;
    //     std::cout<<hand.size()+2<<" Close the card "<<std::endl;
    // }
    size_t option = 0;
    while(true)
    {
        // std::cout<<"Select a card:"<<std::endl;
        renderCallback(isFirst, hand);
        std::cin>>option;
        if(std::cin.fail()) {
            std::cin.clear(); // clear error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        size_t size=this->hand.size();

        if(option>0&&option<=size)
        {
            auto card=this->playCard(option-1, this->hand);
            if(this->hand.size()==5)
                return this->playHand(deck, isFirst);
            std::cout<<this->name<<" played "<<card->toString()<<std::endl;
            return card;
        }
        else if(isFirst && option==size+1){
            this->endRound();
        }
        else if(isFirst && option==size+2 && !this->hasClosedTheCard){
            this->hasClosedTheCard=true;
            this->renderOptions(this->hand);
        }
        else{
            std::cout<<"Not an option"<<std::endl;
        }
    }
}

std::shared_ptr<ICard> Player::playFilteredHand(Deck& deck, bool isFirst, const std::shared_ptr<ICard> &card){
    Hand filteredHand;
    std::vector<uint8_t> reserves;
    //i need to make cards of the same suit as card parameter a priority
    //but i also need to memorize the position of tromfs if there are any
    //in case i don t have cards of the same suit as card parameter
    //using vector<uint8> for small memory size and to avoid keeping track of index
    for(Hand::iterator i = this->hand.begin(); i!= this->hand.end(); ++i)
    {
        int index = std::distance(this->hand.begin(),i);
        if(i->first->compareSuite(*card))
            filteredHand.push_back(std::make_pair(i->first,std::vector<CardOption>{{
                    "",
                    "",
                    [this,index](unsigned){
                        hand.erase(this->hand.begin()+index);
                        }}}));
        else if(i->first->compareSuite(*deck.getTromf()))
            reserves.push_back(index);
    }
    
    if(filteredHand.size()==0 && reserves.size()!=0)
    {
        for(uint8_t i : reserves)
        {
            filteredHand.push_back(std::make_pair(this->hand.at(i).first->clone(),std::vector<CardOption>{{
                    "",
                    "",
                    [this,i](unsigned){
                        hand.erase(this->hand.begin()+i);
                        }}}));
        }
    }

    if(filteredHand.size()==0){
        return this->playHand(deck,isFirst);
    }
    else
    {
        renderOptions(filteredHand);
        size_t option = 0;
        while(true)
        {
            renderCallback(isFirst, filteredHand);
            std::cin>>option;
            if(std::cin.fail()) {
                std::cin.clear(); // clear error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                std::cout << "Invalid input. Try again.\n";
                continue;
            }
            if(option>0&&option<=filteredHand.size())
            {
                auto card=this->playCard(option-1, filteredHand, true);
                std::cout<<this->name<<" played "<<card->toString()<<std::endl;
                return card;
            }
            else{
                std::cout<<"Not an option"<<std::endl;
            }
        }
    }
}

void Player::calculateOptions(Deck& deck){
    for(Hand::iterator i = this->hand.begin(); i!= this->hand.end(); ++i){
        if(i->first->compareSuite(*deck.getTromf())) 
        {
            if(i->first->getEasyRank()==2&&deck.cardsLeft()>=4){
                i->second.push_back({
                    "Play",
                    "Play card with no special effect",
                    [this](unsigned position){
                        hand.erase(hand.begin() + position);
                        }
                });
                i->second.push_back({
                    "Change Tromf",
                    "Change with the Tromf card "+(*deck.getTromf()).toString(),
                    [this,&deck, card = i->first](unsigned /*position*/){
                        this->changeTromf(card,deck);
                    }
                });
            }
            else if(i->first->getEasyRank()==3 || i->first->getEasyRank()==4)   
            for(Hand::const_iterator j = this->hand.begin(); j!= this->hand.end(); ++j){
                if(i->first->compareSuite(*j->first) //if cards are of the same Suite
                && i->first->getEasyRank() != j->first->getEasyRank()// and ranks are different (first card is 3 or 4)
                && (j->first->getEasyRank()==3||j->first->getEasyRank()==4))// and second card is 3 or 4
                {
                    i->second.push_back({
                        "Play",
                        "Play card with no special effect",
                        [this](unsigned position){
                            hand.erase(hand.begin() + position);
                            }
                    });
                    i->second.push_back({
                        "40",
                        "Call 40",
                        [this](unsigned position){if(this->score>0)
                                this->addScore(40);
                            else
                               this->latentPoints+=40;
                            hand.erase(hand.begin() + position);
                            }
                    });
                    i->second.push_back({
                        "40 END",
                        "Call 40 and end the round",
                        [this](unsigned position){
                            if(this->score>0)
                                this->addScore(40);
                            else
                               this->latentPoints+=40;
                            hand.erase(hand.begin() + position);
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
                        "Play",
                        "Play card with no special effect",
                        [this](unsigned position){
                            hand.erase(hand.begin() + position);
                            }
                    });
                    i->second.push_back({
                        "20",
                        "Call 20",
                        [this](unsigned position){
                            if(this->score>0)
                                this->addScore(20);
                            else
                               this->latentPoints+=20;
                            hand.erase(hand.begin() + position);
                            }
                    });
                    i->second.push_back({
                        "20 END",
                        "Call 20 and end the round",
                        [this](unsigned position){
                            if(this->score>0)
                                this->addScore(20);
                            else
                               this->latentPoints+=20;
                            hand.erase(hand.begin() + position);
                            this->endRound();
                        }
                    });
                }
            }
    }
}

void Player::renderOptions(const Hand& hand)const{
    std::cout<<this->name<<", here are your options:"<<std::endl;
    for(Hand::const_iterator i = hand.cbegin(); i!= hand.cend(); ++i)
    {
        std::cout<<std::distance(hand.cbegin(),i)+1<<" "<<i->first->toString();
        if(!i->second.empty()){
            std::cout<<" (";
            for(std::vector<CardOption>::const_iterator j = i->second.begin(); j!= i->second.end(); ++j)
                std::cout<<j->shortDescription<<", ";
            std::cout<<")";
        }
        std::cout<<std::endl;
    }
}

void Player::drawCard(Deck& deck){
    auto card = deck.drawCard();
    if(card&&hand.size()<=MAX_HAND_SIZE){
        hand.push_back(std::make_pair(card, std::vector<CardOption>{}));
        //hand.push_back({card, {}});
    }
}

std::shared_ptr<ICard> Player::playCard(const unsigned& cardPosition,Hand& hand, bool isFilteredHand){
    auto& cardEntry = hand.at(cardPosition);
    auto card = cardEntry.first->clone();
    if(cardEntry.second.empty()){
        hand.erase(hand.begin() + cardPosition);
        return card;
    }
    else{
        if(!isFilteredHand){
            for(std::vector<CardOption>::iterator i = cardEntry.second.begin(); i!= cardEntry.second.end(); ++i)
                std::cout<<std::distance(cardEntry.second.begin(),i)+1<<" "<<i->description<<std::endl;
            size_t option=0;
            while(true)
            {
                std::cin>>option;
                if(option>0 && option<=cardEntry.second.size()){
                    cardEntry.second.at(option-1).action(cardPosition);//Normally i would erase the card outside of the lambda but there is an option to do something without playing a card
                    break;
                }
                else{
                    std::cout<<"Not an option, try again"<<std::endl;
                }
            }
        }
        else{
            cardEntry.second.at(0).action(cardPosition);
        }
        
        return card;
    }    
}

void Player::endRound(){
    std::cout<<"END GAME HERE"<<std::endl;
    endGameCallback();
}

void Player::addScore(const unsigned &points)
{
    this->score+=points;
    this->score+=this->latentPoints;
    this->latentPoints=0;
}

void Player::changeTromf(std::shared_ptr<ICard> card, Deck& deck){
    auto copy=deck.getTromf();

    if(!copy || !card)
        return;
        
    auto handCopy = card->clone();
    card->changeCard(*copy);
    copy->changeCard(*handCopy);
    renderCallback(true,hand);
}

size_t Player::getCurrentHandSize()const{
    return this->hand.size();
}

bool Player::getHasClosedTheCard()const{
    return hasClosedTheCard;
}

unsigned Player::getScore()const{
    return this->score;
}

void Player::addRoundsWon(const unsigned &points){
    this->roundsWon+=points;
}

unsigned Player::getRoundsWon()const{
    return this->roundsWon;
}

void Player::resetPlayerForNewRound(){
    this->hand.clear();
    this->score=0;
    this->hasClosedTheCard=false;
    this->latentPoints=0;
}

std::string Player::getName() const{
    return this->name;
}