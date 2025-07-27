
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

int main(){
    const std::string imagePath = "resources/cards/acorn-ace.png";

    //initialize SDL2 core video system
    if(SDL_Init(SDL_INIT_VIDEO) !=0){
        std::cerr << "SDL_Init Error: "<<SDL_GetError() << "\n";
        return 1;
    }

    //Initialize SDL2_Image with PNG suppoty
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        std::cerr << "IMG_Init Error: "<<IMG_GetError() << "\n";
        return 1;
    }

    //Initialize SDL2_ttf for text rendering
    if(TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: "<<TTF_GetError() << "\n";
        return 1;
    }

    //Create window 1000x600
    SDL_Window* window = SDL_CreateWindow(
        "Card Viewer",   //title
        SDL_WINDOWPOS_CENTERED, // X position
        SDL_WINDOWPOS_CENTERED, // Y position
        1000, // Width
        600, // Height
        0 //flags (0 = no extra features)
    );

    if(!window){
        std::cerr << "Window creation error: "<<SDL_GetError() << "\n";
        return 1;
    }

    // create a hardware-accelerated renderer for window
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    if(!renderer)
    {
        std::cerr << "Renderer creation Error: " << SDL_GetError() << "\n";
        return 1;
    }

    //Load the PNG card image into an SDL surface
    SDL_Surface* surface = IMG_Load(imagePath.c_str());

    if(!surface){
        std::cerr << "Image Load Error: " << IMG_GetError() << "\n";
        return 1;
    }

    //Convert the surface to a GPU-optimized texture
    SDL_Texture* cardTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); //No longer needed after creating the texture

    if(!cardTexture){
        std::cerr<< "Texture Creation Error: "<< SDL_GetError() <<"\n";
        return 1;
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if(!font){
        std::cerr << "Font Load Error: " << TTF_GetError() << "\n";
        return 1;
    }

    //Define where on screen the card image will be drawn
    SDL_Rect cardRect = { 300, 150, 200, 300 }; //x, y, width, height

    //Variable to track how many times card was clicked
    int clickCounter=0;

    //Event loop flag
    bool running = true;
    
    //SDL event structure used for all types of input
    SDL_Event e;

    //Main event loop
    while(running){
        //Handle all pending events
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT){
                running = false;
            }
            else if( e.type == SDL_MOUSEBUTTONDOWN) {
                //Mouse click detected
                int x = e.button.x;
                int y = e.button.y;

                //Check if click occured inside the card's bounding box
                if( x >= cardRect.x && 
                    x <= cardRect.x + cardRect.w &&
                    y >= cardRect.y &&
                    y <= cardRect.y + cardRect.h)
                {
                    clickCounter++;
                }
            }
        }

        //Clear the screen (dark grey backgrownd)
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Draw the card image
        SDL_RenderCopy(renderer, cardTexture, nullptr, &cardRect);

        // Create a text string like "Clicks: 5"
        std::string text = "Clicks: " + std::to_string(clickCounter);

        // Set the font color (white)
        SDL_Color textColor = { 255, 255, 255 };

        // Render text to a surface
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Define where the text will appear on the window
        SDL_Rect textRect = { 20, 20, textSurface->w, textSurface->h };

        // Copy the rendered text to the screen
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        // Clean up the temporary text surface and texture
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        // Present the final frame to the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup all resources
    SDL_DestroyTexture(cardTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}