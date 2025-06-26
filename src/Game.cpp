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
    magyarDeck->shuffleDeck();
    magyarDeck->shuffleDeck();
    magyarDeck->shuffleDeck();

    std::cout<< std::endl << "Printing the Magyar Deck after shuffling"<<std::endl;
    magyarDeck->printDeck();

    std::cout<< std::endl << "Creating a Player"<<std::endl;
    Player p1(PlayerType::Player, [this]() { std::cout<<"ENDING the game"<<std::endl; });
    Player p2(PlayerType::NPC, [this]() { std::cout<<"ENDING the game"<<std::endl; });
    std::cout<< std::endl << "Drawing cards"<<std::endl;
    p1.drawCard(*magyarDeck);
    p2.drawCard(*magyarDeck);
    p1.drawCard(*magyarDeck);
    p2.drawCard(*magyarDeck);
    p1.drawCard(*magyarDeck);
    p2.drawCard(*magyarDeck);
    p1.drawCard(*magyarDeck);
    p2.drawCard(*magyarDeck);
    p1.drawCard(*magyarDeck);
    p2.drawCard(*magyarDeck);

    std::cout<< std::endl << "Player 1 Showing the hand"<<std::endl;
    p1.calculateOptions(*magyarDeck);
    p1.renderOptions();
    std::cout<< std::endl << "Player 1 Showing the hand"<<std::endl;
    p2.calculateOptions(*magyarDeck);
    p2.renderOptions();

    std::cout<<p1.playCard(1)->toString()<<std::endl;
    std::cout<<p1.playCard(1)->toString()<<std::endl;

}
