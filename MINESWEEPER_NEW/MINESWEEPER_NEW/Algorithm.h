#pragma once
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "GameMap.h"

extern SDL_Surface* img_menu = NULL;

// T?o bản đồ mìn
void create_board(int m, int n, int k, std::vector<std::vector<bool>>& board) {
    //Random mìn trong bảng
    srand(time(0));
    int mine = 0;
    while (mine < k)
    {
        int i = rand() % m;
        int j = rand() % n;
        if (board[i][j] == true) continue;
        board[i][j] = true;
        mine++;
    }
}

// Tìm số luợng mìn xung quanh ô
int count_mines(int m, int n, std::vector<std::vector<bool>>& board, int row, int col) {
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < m && j >= 0 && j < n && board[i][j]) {
                count++;
            }
        }
    }
    return count;
}


// Duyệt theo chiều rộng dò tìm các ô không có mìn xung quanh ô dã được mở
void bfs(int m, int n, std::vector<std::vector<bool>>& board, std::vector<std::vector<bool>>& visited, int row, int col) {
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(row, col));
    visited[row][col] = true;
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int i = r - 1; i <= r + 1; i++) {
            for (int j = c - 1; j <= c + 1; j++) {
                if (i >= 0 && i < m && j >= 0 && j < n && !board[i][j] && !visited[i][j]) {
                    visited[i][j] = true;
                    if (count_mines(m, n, board, i, j) == 0) {
                        q.push(std::make_pair(i, j));
                    }
                }
            }
        }
    }
}




#endif // !ALGORITHM_H
