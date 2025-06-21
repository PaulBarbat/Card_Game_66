#include "CardFactory.hpp"

using namespace tinyxml2;

std::shared_ptr<Deck> CardFactory::createDeckFromXML(DeckType type, const std::string& path){
    switch(type){
        case DeckType::Classic:
            return createClassicDeckFromXML(path);
        case DeckType::Magyar:
            return createMagyarDeckFromXML(path);
        default:
            throw std::invalid_argument("Unsupported deck type");
    }
}

std::shared_ptr<Deck> CardFactory::createClassicDeckFromXML(const std::string& path){
    XMLDocument doc;
    Deck deck;

    if(doc.LoadFile(path.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Failed to load XML from file "+path);
    
    //Getting the root of the Deck
    auto* root = doc.FirstChildElement("Deck");
    if(!root)
        throw std::runtime_error("Missing <Deck> Element "+path);

    //Getting all elements in Deck
    for(auto* card = root->FirstChildElement("Card"); card; card = card->NextSiblingElement("Card")){
        std::string suitStr = card->FirstChildElement("Suite")->GetText();
        std::string rankStr = card->FirstChildElement("Rank")->GetText();

        ClassicSuit suit;
        ClassicRank rank;

        //get the suit
        if(suitStr == "Hearts") suit = ClassicSuit::Hearts;
        else if(suitStr == "Diamonds") suit = ClassicSuit::Diamonds;
        else if(suitStr == "Clubs") suit = ClassicSuit::Clubs;
        else if(suitStr == "Spades") suit = ClassicSuit::Spades;
        else throw std::runtime_error("Invalid suit: " + suitStr);

        //get the rank
        if(rankStr == "Two") rank = ClassicRank::Two;
        else if(rankStr == "Three") rank = ClassicRank::Three;
        else if(rankStr == "Four") rank = ClassicRank::Four;
        else if(rankStr == "Ten") rank = ClassicRank::Ten;
        else if(rankStr == "Ace") rank = ClassicRank::Ace;
        else throw std::runtime_error("Invalid rank: " + rankStr);

        //add the card to the deck
        deck.addCard(std::make_shared<Card<ClassicSuit,ClassicRank>>(suit,rank));
    }
    return std::make_shared<Deck>(deck);
}

std::shared_ptr<Deck> CardFactory::createMagyarDeckFromXML(const std::string& path){
    XMLDocument doc;
    Deck deck;

    if(doc.LoadFile(path.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Failed to load XML from file "+path);
    
    //Getting the root of the Deck
    auto* root = doc.FirstChildElement("Deck");
    if(!root)
        throw std::runtime_error("Missing <Deck> Element "+path);

    //Getting all elements in Deck
    for(auto* card = root->FirstChildElement("Card"); card; card = card->NextSiblingElement("Card")){
        std::string suitStr = card->FirstChildElement("Suite")->GetText();
        std::string rankStr = card->FirstChildElement("Rank")->GetText();

        MagyarSuit suit;
        MagyarRank rank;

        //get the suit
        if(suitStr == "Rosu") suit = MagyarSuit::Rosu;
        else if(suitStr == "Verde") suit = MagyarSuit::Verde;
        else if(suitStr == "Ghinda") suit = MagyarSuit::Ghinda;
        else if(suitStr == "Bata") suit = MagyarSuit::Bata;
        else throw std::runtime_error("Invalid suit: " + suitStr);

        //get the rank
        if(rankStr == "Doi") rank = MagyarRank::Doi;
        else if(rankStr == "Trei") rank = MagyarRank::Trei;
        else if(rankStr == "Cal") rank = MagyarRank::Cal;
        else if(rankStr == "Craita") rank = MagyarRank::Craita;
        else if(rankStr == "Tuz") rank = MagyarRank::Tuz;
        else throw std::runtime_error("Invalid rank: " + rankStr);

        //add the card to the deck
        deck.addCard(std::make_shared<Card<MagyarSuit,MagyarRank>>(suit,rank));
    }
    return std::make_shared<Deck>(deck);
}
