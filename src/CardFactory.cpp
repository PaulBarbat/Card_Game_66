#include "CardFactory.hpp"

using namespace tinyxml2;

std::shared_ptr<Deck> CardFactory::createDeckFromXML(DeckType type, const std::string& path){
    std::cout<< "Inside the createDeckFromXML"<<std::endl;
    std::cin.get(); 
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
    std::cout<< "Inside the createDeckFromXML"<<std::endl;
    std::cin.get(); 
    if(doc.LoadFile(path.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Failed to load XML from file "+path);
    std::cout<< "1"<<std::endl;
    std::cin.get(); 
    //Getting the root of the Deck
    auto* root = doc.FirstChildElement("Deck");
    if(!root)
        throw std::runtime_error("Missing <Deck> Element "+path);
    std::cout<< "2"<<std::endl;
    std::cin.get(); 
    //Getting all elements in Deck
    for(auto* card = root->FirstChildElement("Card"); card; card = card->NextSiblingElement("Card")){
        std::cout<< "M"<<std::endl;
        std::cin.get(); 
        std::string suiteStr = card->FirstChildElement("Suitee")->GetText();
        std::cout<< "M"<<std::endl;
        std::cin.get(); 
        std::string rankStr = card->FirstChildElement("Rank")->GetText();
        std::cout<< "3"<<std::endl;
        std::cin.get(); 
        ClassicSuite suite;
        ClassicRank rank;

        //get the suite
        if(suiteStr == "Hearts") suite = ClassicSuite::Hearts;
        else if(suiteStr == "Diamonds") suite = ClassicSuite::Diamonds;
        else if(suiteStr == "Clubs") suite = ClassicSuite::Clubs;
        else if(suiteStr == "Spades") suite = ClassicSuite::Spades;
        else throw std::runtime_error("Invalid suite: " + suiteStr);
        std::cout<< "4"<<std::endl;
        std::cin.get(); 
        //get the rank
        if(rankStr == "Two") rank = ClassicRank::Two;
        else if(rankStr == "Three") rank = ClassicRank::Three;
        else if(rankStr == "Four") rank = ClassicRank::Four;
        else if(rankStr == "Ten") rank = ClassicRank::Ten;
        else if(rankStr == "Ace") rank = ClassicRank::Ace;
        else throw std::runtime_error("Invalid rank: " + rankStr);
        std::cout<< "5"<<std::endl;
        std::cin.get(); 
        //add the card to the deck
        deck.addCard(std::make_shared<Card<ClassicSuite,ClassicRank>>(suite,rank));
    }
    return std::make_shared<Deck>(deck);
}

std::shared_ptr<Deck> CardFactory::createMagyarDeckFromXML(const std::string& path){
    XMLDocument doc;
    Deck deck;
    std::cout<< "M"<<std::endl;
    std::cin.get(); 
    if(doc.LoadFile(path.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Failed to load XML from file "+path);
    std::cout<< "M"<<std::endl;
    std::cin.get(); 
    //Getting the root of the Deck
    auto* root = doc.FirstChildElement("Deck");
    if(!root)
        throw std::runtime_error("Missing <Deck> Element "+path);
    std::cout<< "M"<<std::endl;
    std::cin.get(); 
    //Getting all elements in Deck
    for(auto* card = root->FirstChildElement("Card"); card; card = card->NextSiblingElement("Card")){
        std::cout<< "M"<<std::endl;
        std::cin.get(); 
        std::string suiteStr = card->FirstChildElement("Suitee")->GetText();
        std::cout<< "M"<<std::endl;
        std::cin.get(); 
        std::string rankStr = card->FirstChildElement("Rank")->GetText();

        MagyarSuite suite;
        MagyarRank rank;

        //get the suite
        if(suiteStr == "Rosu") suite = MagyarSuite::Rosu;
        else if(suiteStr == "Verde") suite = MagyarSuite::Verde;
        else if(suiteStr == "Ghinda") suite = MagyarSuite::Ghinda;
        else if(suiteStr == "Bata") suite = MagyarSuite::Bata;
        else throw std::runtime_error("Invalid suite: " + suiteStr);

        //get the rank
        if(rankStr == "Doi") rank = MagyarRank::Doi;
        else if(rankStr == "Trei") rank = MagyarRank::Trei;
        else if(rankStr == "Cal") rank = MagyarRank::Cal;
        else if(rankStr == "Craita") rank = MagyarRank::Craita;
        else if(rankStr == "Tuz") rank = MagyarRank::Tuz;
        else throw std::runtime_error("Invalid rank: " + rankStr);

        //add the card to the deck
        deck.addCard(std::make_shared<Card<MagyarSuite,MagyarRank>>(suite,rank));
    }
    return std::make_shared<Deck>(deck);
}
