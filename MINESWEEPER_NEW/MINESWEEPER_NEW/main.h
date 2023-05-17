#pragma once
#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS

#include"Algorithm.h"
#include"Init.h"
#include"MouseEvent.h"

void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int gamequit = 0;

void ShowgameScreen(int k)
{
    gFont = TTF_OpenFont("font/font.ttf", 80); // ???ng d?n ??n t?p font t??ng ?ng
    bool quit = false;
    std::vector<std::vector<bool>> board(MAP_WIDTH, std::vector<bool>(MAP_HEIGHT, false));
    create_board(MAP_WIDTH, MAP_HEIGHT, k, board);
    int num_opened = 0;

    // TODO: Kh?i t?o và c?u hình màn hình game

    Uint32 startTime = SDL_GetTicks();
    // Th?i gian ch?y theo giây
    float elapsedTime = 0.0f;

    // Vòng l?p chính
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            int row = -1;
            int col = -1;
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Tính toán v? trí c?a ô ???c ch?n
                row = event.button.x / TILE_SIZE;
                col = event.button.y / TILE_SIZE;

                SDL_QueryTexture(map[row][col], &covered, NULL, NULL, NULL);

                if (event.button.button == SDL_BUTTON_LEFT)
                {

                    // ki?m tra ô ??y ?ã ?c m? hay ch?a
                    if (covered1 != covered && covered2 != covered || flagmap[row][col] == 2)
                    {
                        std::cout << "This cell has already been opened! Try again2." << std::endl;
                        continue;
                    }
                    // Ki?m tra có mìn hay không
                    if (board[row][col]) {
                        Mix_PlayChannel(-1, g_sound_bullet[1], 0);
                        gamequit = 2;
                        std::cout << "YOU'RE DEAD!" << std::endl;
                        for (int i = 0; i < MAP_WIDTH; i++)
                        {
                            for (int j = 0; j < MAP_HEIGHT; j++)
                            {
                                if (board[i][j])
                                {
                                    if (i == row && j == col)
                                    {
                                        map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom-cell1.png"));
                                    }
                                    else
                                    {
                                        if (i % 2 == 0)
                                        {
                                            if (j % 2 == 0)
                                            {
                                                map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom1.png"));
                                            }
                                            else
                                            {
                                                map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom0.png"));
                                            }
                                        }
                                        else
                                        {
                                            if (j % 2 == 1)
                                            {
                                                map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom1.png"));
                                            }
                                            else
                                            {
                                                map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom0.png"));
                                            }
                                        }
                                    }
                                    flagmap[i][j] = 1;
                                }
                            }
                        }
                        // quit = true
                    }

                    else {

                        Mix_PlayChannel(-1, g_sound_bullet[0], 0);

                        // Ð?m s? lu?ng mìn xung quanh ô dã m?
                        int count = count_mines(MAP_WIDTH, MAP_HEIGHT, board, row, col);
                        if (count == 0)
                        {

                            if (row % 2 == 0)
                            {
                                if (col % 2 == 0)
                                {
                                    map[row][col] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_0.png"));
                                }
                                else
                                {
                                    map[row][col] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_1.png"));
                                }
                            }
                            else
                            {
                                if (col % 2 == 1)
                                {
                                    map[row][col] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_0.png"));
                                }
                                else
                                {
                                    map[row][col] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_1.png"));
                                }
                            }
                            flagmap[row][col] = 1;
                        }
                        else
                        {
                            if (row % 2 == 0)
                            {
                                if (col % 2 == 0)
                                {
                                    map[row][col] = numTextures[count];
                                }
                                else
                                {
                                    map[row][col] = numTextures[count + 8];
                                }
                            }
                            else
                            {
                                if (col % 2 == 1)
                                {
                                    map[row][col] = numTextures[count];
                                }
                                else
                                {
                                    map[row][col] = numTextures[count + 8];
                                }
                            }
                            flagmap[row][col] = 1;
                        }
                        num_opened++;

                        // N?u không có mìn xung quanh, duy?t tìm các ô không có mìn xung quanh
                        if (count == 0) {
                            std::vector<std::vector<bool>> visited(MAP_WIDTH, std::vector<bool>(MAP_HEIGHT, false));
                            bfs(MAP_WIDTH, MAP_HEIGHT, board, visited, row, col);
                            for (int i = 0; i < MAP_WIDTH; i++) {
                                for (int j = 0; j < MAP_HEIGHT; j++) {
                                    if (visited[i][j]) {
                                        int count = count_mines(MAP_WIDTH, MAP_HEIGHT, board, i, j);
                                        if (count == 0)
                                        {
                                            if (i % 2 == 0)
                                            {
                                                if (j % 2 == 0)
                                                {
                                                    map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_0.png"));
                                                }
                                                else
                                                {
                                                    map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_1.png"));
                                                }
                                            }
                                            else
                                            {
                                                if (j % 2 == 1)
                                                {
                                                    map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_0.png"));
                                                }
                                                else
                                                {
                                                    map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/1_1.png"));
                                                }
                                            }
                                            flagmap[i][j] = 1;
                                        }
                                        else
                                        {
                                            if (i % 2 == 0)
                                            {
                                                if (j % 2 == 0)
                                                {
                                                    map[i][j] = numTextures[count];
                                                }
                                                else
                                                {
                                                    map[i][j] = numTextures[count + 8];
                                                }
                                            }
                                            else
                                            {
                                                if (j % 2 == 1)
                                                {
                                                    map[i][j] = numTextures[count];
                                                }
                                                else
                                                {
                                                    map[i][j] = numTextures[count + 8];
                                                }
                                            }
                                            flagmap[i][j] = 1;
                                        }
                                        num_opened++;
                                    }
                                }
                            }
                        }
                        std::cout << num_opened << std::endl;
                        // Ki?m tra dã m? h?t các ô không có mìn chua
                        if (num_opened-1 == MAP_WIDTH * MAP_HEIGHT - k) {
                            std::cout << "YOU WIN!" << std::endl;
                            gamequit = 1;
                            for (int i = 0; i < MAP_WIDTH; i++)
                            {
                                for (int j = 0; j < MAP_HEIGHT; j++)
                                {
                                    if (board[i][j])
                                    {
                                        if (i % 2 == 0)
                                        {
                                            if (j % 2 == 0)
                                            {
                                                map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom1.png"));
                                            }
                                            else
                                            {
                                                map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom0.png"));
                                            }
                                        }
                                        else
                                        {
                                            if (j % 2 == 1)
                                            {
                                                map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom1.png"));
                                            }
                                            else
                                            {
                                                map[i][j] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/boom0.png"));
                                            }
                                        }
                                        flagmap[row][col] = 3;


                                    }
                                }
                            }

                            Mix_PlayChannel(-1, g_sound_exp[0], 0);

                            
                            //quit = true;
                        }
                    }
                }

                else
                {
                    if (flagmap[row][col] == 0)
                    {
                        std::cout << "no" << std::endl;
                        if (row % 2 == 0)
                        {
                            if (col % 2 == 0)
                            {
                                map[row][col] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/flag0.png"));
                            }
                            else
                            {
                                map[row][col] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/flag1.png"));
                            }
                        }
                        else
                        {
                            if (col % 2 == 1)
                            {
                                map[row][col] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/flag0.png"));
                            }
                            else
                            {
                                map[row][col] = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/flag1.png"));
                            }
                        }
                        flagmap[row][col] = 2;
                    }
                    else if (flagmap[row][col] == 2) // ?ã ??t c?
                    {
                        std::cout << "yes" << std::endl;
                        if (row % 2 == 0)
                        {
                            if (col % 2 == 0)
                            {
                                map[row][col] = tileTextures[Tile::COVERED1];
                            }
                            else
                            {
                                map[row][col] = tileTextures[Tile::COVERED2];
                            }
                        }
                        else
                        {
                            if (col % 2 == 1)
                            {
                                map[row][col] = tileTextures[Tile::COVERED1];
                            }
                            else
                            {
                                map[row][col] = tileTextures[Tile::COVERED2];
                            }
                        }
                        flagmap[row][col] = 0;//ô tr?ng ch?a ??t c?
                    }
                }

                break;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
                handleMouseEvent(event);
                break;
            default:
                break;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - startTime;
        startTime = currentTime;

        // C?p nh?t th?i gian ch?y theo giây
        elapsedTime += deltaTime / 1000.0f;

        char timeText[10];
        sprintf(timeText, "%.1f", elapsedTime);
        TTF_Font* Font = TTF_OpenFont("font/font.ttf", 40);

        // Xóa màn hình
        //SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        // V? các ?nh lên màn hình
        drawMap(renderer);
        // Hi?n th? màn hình
        SDL_RenderPresent(renderer);
        if (gamequit == 1)
        {
            RenderText(renderer, gFont, "YOU WIN", 250, 200, { 255 , 0 , 0 });
            RenderText(renderer, gFont, "GAME OVER!", 210, 300, { 255 , 0 , 0 });
            RenderText(renderer, Font, "Score:", 320, 400, { 0 , 0 , 255 });
            RenderText(renderer, Font, timeText, 550, 400, { 0 , 0 , 255 });

            Mix_PlayChannel(-1, g_sound_exp[0], 0);

            SDL_RenderPresent(renderer);

            // ??i ng??i ch?i nh?n phím ?? thoát
            bool keyPressed = false;
            while (!keyPressed)
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                        keyPressed = true;
                    }
                    else if (event.type == SDL_KEYDOWN)
                    {
                        keyPressed = true;
                    }
                }
            }
            quit = true; // Thoát kh?i vòng l?p khi hi?n th? thông báo
        }
        else if (gamequit == 2)
        {
            RenderText(renderer, gFont, "YOU LOSS", 250, 200, { 255 , 0 , 0 });
            RenderText(renderer, gFont, "GAME OVER!", 210, 300, { 255 , 0 , 0 });
            RenderText(renderer, Font, "Score:", 320, 400, {0 , 0 , 255});
            RenderText(renderer, Font, timeText, 550, 400, { 0 , 0 , 255 });

            SDL_RenderPresent(renderer);

            // ??i ng??i ch?i nh?n phím ?? thoát
            bool keyPressed = false;
            while (!keyPressed)
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                        keyPressed = true;
                    }
                    else if (event.type == SDL_KEYDOWN)
                    {
                        keyPressed = true;
                    }
                }
            }
            quit = true; // Thoát kh?i vòng l?p khi hi?n th? thông báo
        }
    }

    // TODO: Gi?i phóng các tài nguyên liên quan ??n màn hình game
    // Gi?i phóng các texture
    cleanup();
    SDL_DestroyTexture(backgroundTexture);

    // Update the screen
    SDL_RenderPresent(renderer);

    // ?óng SDL_Image
    IMG_Quit();

    // ?óng SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ShowMenu()
{
    gFont = TTF_OpenFont("font/font.ttf", 30); // ???ng d?n ??n t?p font t??ng ?ng
    TTF_Font* Font = TTF_OpenFont("font/font.ttf", 50);
    bool quit = false;
    SDL_Event e;

    SDL_Color textColo = { 0, 255, 0 }; // Màu xanh lá cây
    SDL_Color textColo1 = { 0, 0, 255 };

    while (!quit)
    {

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN|| e.type == SDL_MOUSEMOTION)
            {
                int mouseX = e.button.x;
                int mouseY = e.button.y;
                
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (mouseX >= 360 && mouseX <= 600 && mouseY >= 300 && mouseY <= 330)
                    {
                        // Ch? ?? ch?i d? ???c ch?n
                        ShowgameScreen(80);
                    }
                    else if (mouseX >= 350 && mouseX <= 600 && mouseY >= 350 && mouseY <= 380)
                    {
                        // Ch? ?? ch?i trung bình ???c ch?n
                        ShowgameScreen(110);
                    }
                    else if (mouseX >= 360 && mouseX <= 600 && mouseY >= 400 && mouseY <= 430)
                    {
                        // Ch? ?? ch?i khó ???c ch?n
                        ShowgameScreen(130);
                    }
                }
                if (e.type == SDL_MOUSEMOTION)
                {
                    SDL_RenderClear(renderer);

                    SDL_Texture* menuBackground = SDL_CreateTextureFromSurface(renderer, IMG_Load("Maps/menu.jpg"));
                    SDL_RenderCopy(renderer, menuBackground, nullptr, nullptr);


                    RenderText(renderer, Font, "Mine Sweeper", 260, 200, textColo);
                    RenderText(renderer, gFont, "1. Easy", 360, 300, textColo);
                    RenderText(renderer, gFont, "2. Medium", 350, 350, textColo);
                    RenderText(renderer, gFont, "3. Hard", 360, 400, textColo);

                    if (mouseX >= 360 && mouseX <= 600 && mouseY >= 300 && mouseY <= 330)
                    {
                        RenderText(renderer, gFont, "1. Easy", 360, 300, textColo1);
                    }
                    if (mouseX >= 350 && mouseX <= 600 && mouseY >= 350 && mouseY <= 380)
                    {
                        RenderText(renderer, gFont, "2. Medium", 350, 350, textColo1);
                    }

                    if (mouseX >= 360 && mouseX <= 600 && mouseY >= 400 && mouseY <= 430)
                    {
                        RenderText(renderer, gFont, "3. Hard", 360, 400, textColo1);
                    }
                    SDL_RenderPresent(renderer);
                }
            }
        }

      
    }
}



#endif // !MAIN_H
