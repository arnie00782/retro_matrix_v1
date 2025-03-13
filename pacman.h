#ifndef PACMAN_H
#define PACMAN_H

#include "led-matrix.h"
#include <vector>

struct Point {
    int x, y;
};

class PacMan {
public:
    Point position;
    rgb_matrix::Color color;
    int score;

    PacMan(Point startPos);
    void move(char direction, std::vector<std::vector<int>>& maze);
};

class Ghost {
public:
    Point position;
    rgb_matrix::Color color;

    Ghost(Point startPos, rgb_matrix::Color ghostColor);
    void moveRandom(std::vector<std::vector<int>>& maze);
};

class PacManGame {
public:
    std::vector<std::vector<int>> maze;
    PacMan pacman;
    std::vector<Ghost> ghosts;
    bool running;

    PacManGame();
    void update(char direction);
};

void drawGame(rgb_matrix::Canvas* canvas, PacManGame &game);

#endif
