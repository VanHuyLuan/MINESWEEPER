#pragma once
#ifndef COMMONFUCT_H
#define COMMONFUCT_H

#include<queue>
#include<random>
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<string>
#include <Windows.h>


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
extern TTF_Font* gFont = NULL;


// ??nh ngh?a kích th??c ?nh và kích th??c m?ng 2 chi?u , kích th??c amfn hình
const int TILE_SIZE = 32;
const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 20;
const int WIDTH = TILE_SIZE * MAP_WIDTH;
const int HEIGHT = TILE_SIZE * MAP_HEIGHT ;


static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];


enum Tile {
    NUM_TILE_TYPES = 15, // loai o
    COVERED1, COVERED2, // Ô cờ chưa mở
    EMPTY1, EMPTY2,   // Ô trống
    ONE, ONE1,     // Ô số 1
    TWO, TWO1,    // Ô số 2
    THREE, THREE1,  // Ô số 3
    FOUR, FOUR1,  // Ô số 4
    FIVE, FIVE1,   // Ô số 5
    SIX, SIX1,    // Ô số 6
    SEVEN, SEVEN1,  // Ô số 7
    EIGHT, EIGHT1,   // Ô số 8
    FLAGGED1, FLAGGED2, // Ô đã đánh dấu
    BOOM     // Ô có boom
};


// Khai báo các texture cho từng loại ô trên bản đồ
SDL_Texture* tileTextures[Tile::NUM_TILE_TYPES];


// Khai báo mảng 2 chiều để lưu các ảnh
SDL_Texture* map[MAP_WIDTH][MAP_HEIGHT];
int flagmap[MAP_WIDTH][MAP_HEIGHT] = { 0 };
SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* numTextures[17] = { nullptr };

 Uint32 covered1, covered2, flag1, flag2, covered;


#endif // !COMMONFUCT_H
