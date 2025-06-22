#include "Game.hpp"

Game::Game(){
    std::cout << "This is the Game Constructor"<< std::endl;
}

void Game::run() {
    Card<ClassicSuit, ClassicRank> classic(ClassicSuit::Clubs, ClassicRank::Ten);
    Card<MagyarSuit, MagyarRank> magyar(MagyarSuit::Verde, MagyarRank::Doi);
    std::cout << classic.toString()<<std::endl;
    std::cout << magyar.toString()<<std::endl;
    std::cout << "Hello everyone. This is the game run method" << std::endl;
    std::shared_ptr<Deck> classicDeck = CardFactory::createDeckFromXML(DeckType::Classic, "resources/Clasic_Cards.xml");
    std::shared_ptr<Deck> magyarDeck = CardFactory::createDeckFromXML(DeckType::Magyar, "resources/Magyar_Cards.xml");

    classicDeck->printDeck();
    classicDeck->shuffleDeck();
    classicDeck->printDeck();
    
    magyarDeck->printDeck();
    magyarDeck->shuffleDeck();
    magyarDeck->printDeck();

}
