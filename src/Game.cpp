#include "Game.hpp"

Game::Game(){
    std::cout << "This is the Game Constructor"<< std::endl;
}

void Game::run() {
    Card c = Card(Suit::Clubs, Rank::Four);
    std::cout << "Hello everyone. This is the game run method" << std::endl;
    std::cout << c.toString() << std::endl;
}
