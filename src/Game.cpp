#include "Game.hpp"

Game::Game(){
    std::cout << "This is the Game Constructor"<< std::endl;
}

void Game::run() {
    std::cout<<"Creating a Classic Deck"<<std::endl;
    std::shared_ptr<Deck> classicDeck = CardFactory::createDeckFromXML(DeckType::Classic, "resources/Clasic_Cards.xml");

    
    std::cout<< std::endl << "Printing the Classic Deck"<<std::endl;
    classicDeck->printDeck();

    std::cout<< std::endl << "Shuffling the Classic Deck"<<std::endl;
    classicDeck->shuffleDeck();

    std::cout<< std::endl << "Printing the Classic Deck after shuffling"<<std::endl;
    classicDeck->printDeck();
    
    std::cout<<"Creating a Magyar Deck"<<std::endl;
    std::shared_ptr<Deck> magyarDeck = CardFactory::createDeckFromXML(DeckType::Magyar, "resources/Magyar_Cards.xml");
    
    std::cout<< std::endl << "Printing the Magyar Deck"<<std::endl;
    magyarDeck->printDeck();

    std::cout<< std::endl << "Suffling the Magyar Deck"<<std::endl;
    magyarDeck->shuffleDeck();

    std::cout<< std::endl << "Printing the Magyar Deck after shuffling"<<std::endl;
    magyarDeck->printDeck();

}
