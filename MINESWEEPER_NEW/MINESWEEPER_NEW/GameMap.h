#pragma once
#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "CommonFuct.h"
#include "Init.h"

// Hàm t?i tài nguyên
bool loadResources(SDL_Renderer* renderer)
{

    // T?i ?nh các s? t? 1 ??n 8
    for (int i = 1; i <= 8; i++) {
        std::string fileName = "Maps/number_" + std::to_string(i) + ".png";
        SDL_Surface* numSurface = IMG_Load(fileName.c_str());
        if (numSurface == nullptr) {
            std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
            return false;
        }
        numTextures[i] = SDL_CreateTextureFromSurface(renderer, numSurface);
        if (numTextures[i] == nullptr) {
            std::cerr << "Failed to create number texture: " << SDL_GetError() << std::endl;
            return false;
        }
        SDL_FreeSurface(numSurface);
    }

    for (int i = 1; i <= 8; i++) {
        std::string fileName = "Maps/number_" + std::to_string(i) + "_1" + ".png";
        SDL_Surface* numSurface = IMG_Load(fileName.c_str());
        if (numSurface == nullptr) {
            std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
            return false;
        }
        numTextures[i + 8] = SDL_CreateTextureFromSurface(renderer, numSurface);
        if (numTextures[i + 8] == nullptr) {
            std::cerr << "Failed to create number texture: " << SDL_GetError() << std::endl;
            return false;
        }
        SDL_FreeSurface(numSurface);
    }


    // T?i ?nh các ô c?
    tileTextures[Tile::COVERED1] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/0_0.png"));
    SDL_QueryTexture(tileTextures[Tile::COVERED1], &covered1, NULL, NULL, NULL);
    tileTextures[Tile::COVERED2] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/0_1.png"));
    SDL_QueryTexture(tileTextures[Tile::COVERED2], &covered2, NULL, NULL, NULL);
    tileTextures[Tile::FLAGGED1] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/flag0.png"));
    SDL_QueryTexture(tileTextures[Tile::FLAGGED1], &flag1, NULL, NULL, NULL);
    tileTextures[Tile::FLAGGED2] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/flag1.png"));
    SDL_QueryTexture(tileTextures[Tile::FLAGGED2], &flag2, NULL, NULL, NULL);
    tileTextures[Tile::BOOM] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom-cell.png"));
    // T?i ?nh ô tr?ng và ô s?
    tileTextures[Tile::EMPTY1] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_0.png"));
    tileTextures[Tile::EMPTY2] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_1.png"));
    tileTextures[Tile::ONE] = numTextures[1];
    tileTextures[Tile::TWO] = numTextures[2];
    tileTextures[Tile::THREE] = numTextures[3];
    tileTextures[Tile::FOUR] = numTextures[4];
    tileTextures[Tile::FIVE] = numTextures[5];
    tileTextures[Tile::SIX] = numTextures[6];
    tileTextures[Tile::SEVEN] = numTextures[7];
    tileTextures[Tile::EIGHT] = numTextures[8];
    tileTextures[Tile::ONE1] = numTextures[9];
    tileTextures[Tile::TWO1] = numTextures[10];
    tileTextures[Tile::THREE1] = numTextures[11];
    tileTextures[Tile::FOUR1] = numTextures[12];
    tileTextures[Tile::FIVE1] = numTextures[13];
    tileTextures[Tile::SIX1] = numTextures[14];
    tileTextures[Tile::SEVEN1] = numTextures[15];
    tileTextures[Tile::EIGHT1] = numTextures[16];

    return true;
}


// Load các ?nh t? t?p ?nh vào m?ng 2 chi?u
bool loadMap(SDL_Renderer* renderer) {
    // ???ng d?n t?i th? m?c ch?a các t?p ?nh
    const char* path = "Maps/";

    // background
    if (!loadBackground(renderer, "Maps/closed-cell.png")) {
        std::cerr << "Failed to load background." << std::endl;
        return 1;
    }

    // Load các ?nh vào m?ng 2 chi?u
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            // T?o ???ng d?n t?i t?p ?nh
            std::string filename;
            if (x % 2 == 0)
            {
                if (y % 2 == 0)
                {
                    filename = path + std::to_string(0) + "_" + std::to_string(0) + ".png";
                }
                else
                {
                    filename = path + std::to_string(0) + "_" + std::to_string(1) + ".png";
                }
            }
            else
            {
                if (y % 2 == 1)
                {
                    filename = path + std::to_string(0) + "_" + std::to_string(0) + ".png";
                }
                else
                {
                    filename = path + std::to_string(0) + "_" + std::to_string(1) + ".png";
                }
            }

            // Load ?nh t? t?p ?nh
            SDL_Surface* surface = IMG_Load(filename.c_str());
            if (!surface) {
                std::cerr << "Failed to load image: " << filename << " : " << IMG_GetError() << std::endl;
                return false;
            }

            // Chuy?n ??i ?nh thành texture
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!texture) {
                std::cerr << "Failed to create texture: " << filename << " : " << SDL_GetError() << std::endl;
                return false;
            }

            // L?u texture vào m?ng 2 chi?u
            map[x][y] = texture;

            // Gi?i phóng surface
            SDL_FreeSurface(surface);
        }
    }

    return true;
}

// V? các ?nh lên màn hình
void drawMap(SDL_Renderer* renderer) {

    // V? background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // V? các ?nh t? m?ng 2 chi?u lên màn hình
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            SDL_Rect dest = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            SDL_RenderCopy(renderer, map[x][y], NULL, &dest);
        }
    }
}


#endif // !GAMEMAP_H
