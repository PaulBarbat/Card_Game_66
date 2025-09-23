#include "Player.hpp"

Player::Player(PlayerType type, std::string name) 
    :m_hasClosedTheCard(false),
    m_score(0), 
    m_roundsWon(0),
    m_latentPoints(0), 
    m_type(type), 
    m_name(name), 
    m_hand{}{}
  
void Player::resetPlayerForNewRound(){
    m_hand.clear();
    m_score=0;
    m_hasClosedTheCard=false;
    m_latentPoints=0;
}

void Player::drawCard(Deck& deck){
    auto card = deck.drawCard();
    if(card&&m_hand.size()<=s_MAX_HAND_SIZE){
        m_hand.push_back(card);
        //hand.push_back({card, {}});
    }
}

std::shared_ptr<ICard> Player::getCardById(CardID id){
    for(const auto& card : m_hand)
        if(card.get()->getCardID() == id)
            return card;
    std::cout<<"Returning nullptr "<<rankToString(id.first)<<suiteToString(id.second)<<std::endl;
    return nullptr;
    
}

void Player::removeCard(CardID id){
    int i=0;
    for(const auto& card : m_hand)
    {
        if(card.get()->getCardID() == id)
            break;
        i++;
    }
    if(i<m_hand.size())
        m_hand.erase(m_hand.begin()+i);
}

void Player::changeTromf(std::shared_ptr<ICard> card, Deck& deck){
    auto copy=deck.getTromf();

    if(!copy || !card)
        return;
        
    auto handCopy = card->clone();
    card->changeCard(*copy);
    copy->changeCard(*handCopy);
}

void Player::calculateOptions(int cards_left, const CardID& tromf, std::unordered_map<CardID,std::vector<OptionType>, CardHash, CardEqual> &options){
    options.clear();
    for(Hand::iterator i = m_hand.begin(); i!= m_hand.end(); ++i){
        //we could add the Play option for all the cards but it is unnecessary memory usage for cards that only have that option
        if(i->get()->getCardID().second == tromf.second){
            if(i->get()->getEasyRank()==2 && cards_left>2){
                options[i->get()->getCardID()].emplace_back(OptionType::Play);
                options[i->get()->getCardID()].emplace_back(OptionType::ChangeTromf);
            }else if(i->get()->getEasyRank()==3 || i->get()->getEasyRank()==4){   
                for(Hand::const_iterator j = m_hand.begin(); j!= m_hand.end(); ++j){
                    if(i->get()->compareSuite(*j->get()) //if cards are of the same Suite
                    && i->get()->getEasyRank() != j->get()->getEasyRank()// and ranks are different (first card is 3 or 4)
                    && (j->get()->getEasyRank()==3||j->get()->getEasyRank()==4))// and second card is 3 or 4
                    {
                        options[i->get()->getCardID()].emplace_back(OptionType::Play);
                        options[i->get()->getCardID()].emplace_back(OptionType::Play40);
                        options[i->get()->getCardID()].emplace_back(OptionType::Play40End);
                    }
                }
            }
        }else if(i->get()->getEasyRank()==3 || i->get()->getEasyRank()==4){   
            for(Hand::const_iterator j = m_hand.begin(); j!= m_hand.end(); ++j){
                if(i->get()->compareSuite(*j->get()) //if cards are of the same Suite
                && i->get()->getEasyRank() != j->get()->getEasyRank()// and ranks are different (first card is 3 or 4)
                && (j->get()->getEasyRank()==3||j->get()->getEasyRank()==4))// and second card is 3 or 4
                {
                    options[i->get()->getCardID()].emplace_back(OptionType::Play);
                    options[i->get()->getCardID()].emplace_back(OptionType::Play20);
                    options[i->get()->getCardID()].emplace_back(OptionType::Play20End);
                }
            }
        }
    }
}