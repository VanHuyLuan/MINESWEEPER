#pragma once
#ifndef INIT_H
#define INIT_H

#include"Algorithm.h"

// Kh?i t?o SDL và c?a s?
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int screenWidth, int screenHeight) {
    // Kh?i t?o SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Kh?i t?o c?a s?
    window = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    // Kh?i t?o renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    // Kh?i t?o SDL_Image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Failed to initialize SDL_Image: " << IMG_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        return false;

    //Read file wav audio
    g_sound_bullet[0] = Mix_LoadWAV("Audio/click.wav");
    g_sound_bullet[1] = Mix_LoadWAV("Audio/scratch.wav");
    g_sound_exp[0] = Mix_LoadWAV("Audio/beat.wav");


    if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL )
    {
        return false;
    }

    if (TTF_Init() == -1)
    {
        return false;
    }

    return true;
}



// load Background
bool loadBackground(SDL_Renderer* renderer, const std::string& imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (backgroundTexture == nullptr) {
        std::cerr << "Failed to create background texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    SDL_FreeSurface(surface);
    return true;
}



// Gi?i phóng các texture trong m?ng 2 chi?u
void cleanup() {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            SDL_DestroyTexture(map[x][y]);
        }
    }
}


#endif // !INIT_H
