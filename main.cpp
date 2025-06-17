#include "Game.hpp"

int main(){
    Game game;
    game.run();

    std::cout << " This is from the main " << std::endl;

    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get(); 
    
    return 0;
}