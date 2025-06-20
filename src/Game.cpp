#include "Game.hpp"

Game::Game(){
    std::cout << "This is the Game Constructor"<< std::endl;
}

void Game::run() {
    Card<ClasicSuit, ClasicRank> classic(ClasicSuit::Clubs, ClasicRank::Ten);
    Card<MagyarSuit, MagyarRank> magyar(MagyarSuit::Verde, MagyarRank::Doi);
    std::cout << classic.toString()<<std::endl;
    std::cout << magyar.toString()<<std::endl;
    std::cout << "Hello everyone. This is the game run method" << std::endl;
}
