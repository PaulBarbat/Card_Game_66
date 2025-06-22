#include "Game.hpp"

Game::Game(){
    std::cout << "This is the Game Constructor"<< std::endl;
}

void Game::run() {
    Card<ClassicSuite, ClassicRank> classic(ClassicSuite::Clubs, ClassicRank::Ten);
    Card<MagyarSuite, MagyarRank> magyar(MagyarSuite::Verde, MagyarRank::Doi);
    std::cout << classic.toString()<<std::endl;
    std::cout << magyar.toString()<<std::endl;
    std::cout << "Hello everyone. This is the game run method" << std::endl;
    std::cin.get(); 
    std::shared_ptr<Deck> classicDeck = CardFactory::createDeckFromXML(DeckType::Classic, "resources/Clasic_Cards.xml");
    std::cin.get(); 
    std::shared_ptr<Deck> magyarDeck = CardFactory::createDeckFromXML(DeckType::Magyar, "resources/Magyar_Cards.xml");

    classicDeck->printDeck();
    classicDeck->shuffleDeck();
    classicDeck->printDeck();
    
    magyarDeck->printDeck();
    magyarDeck->shuffleDeck();
    magyarDeck->printDeck();

}
