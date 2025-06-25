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
        std::string suiteStr = card->FirstChildElement("Suite")->GetText();
        std::string rankStr = card->FirstChildElement("Rank")->GetText();
        
        ClassicSuite suite;
        ClassicRank rank;
        unsigned points=0;

        //get the suite
        if(suiteStr == "Hearts") suite = ClassicSuite::Hearts;
        else if(suiteStr == "Diamonds") suite = ClassicSuite::Diamonds;
        else if(suiteStr == "Clubs") suite = ClassicSuite::Clubs;
        else if(suiteStr == "Spades") suite = ClassicSuite::Spades;
        else throw std::runtime_error("Invalid suite: " + suiteStr);
        
        //get the rank
        if(rankStr == "Two"){
            rank = ClassicRank::Two;
            points=2;
        } 
        else if(rankStr == "Three"){
            rank = ClassicRank::Three;
            points=3;
        } 
        else if(rankStr == "Four"){
            rank = ClassicRank::Four;
            points=4;
        } 
        else if(rankStr == "Ten"){
            rank = ClassicRank::Ten;
            points=10;
        } 
        else if(rankStr == "Ace"){
             rank = ClassicRank::Ace;
            points=11;
        }
        else throw std::runtime_error("Invalid rank: " + rankStr);
        
        //add the card to the deck
        deck.addCard(std::make_shared<Card<ClassicSuite,ClassicRank>>(suite,rank,points));
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
        std::string suiteStr = card->FirstChildElement("Suite")->GetText();
        std::string rankStr = card->FirstChildElement("Rank")->GetText();

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

        //add the card to the deck
        deck.addCard(std::make_shared<Card<MagyarSuite,MagyarRank>>(suite,rank,points));
    }
    return std::make_shared<Deck>(deck);
}
