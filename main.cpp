#include "Game.hpp"


int main(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr<<"SDL_Init Error: "<<SDL_GetError() << std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr<<"IMG_Init Error: "<<IMG_GetError() << std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    if(TTF_Init() != 0)
    {
        std::cerr<<"TTF Error: "<<TTF_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    SDL_Window* window = SDL_CreateWindow(
        "Card Game 66",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1200,
        800,
        SDL_WINDOW_SHOWN
    );

    if(!window){
        std::cerr<<"SDL Window Creation Error: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("SDL Window Creation Error");
    } 

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!renderer)
    {
        std::cerr<<"Renderer Creation Error: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("Renderer Creation Error");
    }

    TTF_Font* font = TTF_OpenFont("resources/dejavu-fonts-ttf-2.37/ttf/DejaVuSans.ttf", 24);

    if(!font)
    {
        std::cerr<<"Font Opening Error: "<<TTF_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("Font Opening Error");
    }
    
    std::cout<<"Welcome to CardGame66"<<std::endl;
    std::cout<<"Once you press any key the game will start"<<std::endl;
    std::cin.get();
    Game game{window, renderer, font};

    std::cout << " This is from the main " << std::endl;

    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get(); 
    
    return 0;
}