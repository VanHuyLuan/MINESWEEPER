
#include "main.h"

int main(int argc, char* args[]) {

    if (!initSDL(window, renderer, WIDTH, HEIGHT)) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }


    if (loadResources(renderer) == false)
    {
        std::cerr << "failed !" << std::endl;
        return 1;
    }


    // Clear the screen
    SDL_RenderClear(renderer);

    // Draw the background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    if (!loadMap(renderer)) {
        std::cerr << "Failed to load map." << std::endl;
        return 1;
    }

    ShowMenu();


    return 0;
}