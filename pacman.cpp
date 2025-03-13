#include "pacman.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <thread>

using namespace std;
using namespace rgb_matrix;

PacMan::PacMan(Point startPos) : position(startPos), color(Color(255, 255, 0)), score(0) {}

void PacMan::move(char direction, vector<vector<int>>& maze) {
    Point newPos = position;
    if (direction == 'U') newPos.y--;
    else if (direction == 'D') newPos.y++;
    else if (direction == 'L') newPos.x--;
    else if (direction == 'R') newPos.x++;

    if (maze[newPos.y][newPos.x] != 1) {
        position = newPos;
        if (maze[position.y][position.x] == 2) {
            score += 10;
            maze[position.y][position.x] = 0;
        }
    }
}

Ghost::Ghost(Point startPos, Color ghostColor) : position(startPos), color(ghostColor) {}

void Ghost::moveRandom(vector<vector<int>>& maze) {
    vector<Point> moves = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    random_shuffle(moves.begin(), moves.end());
    for (auto move : moves) {
        Point newPos = {position.x + move.x, position.y + move.y};
        if (maze[newPos.y][newPos.x] != 1) {
            position = newPos;
            break;
        }
    }
}

PacManGame::PacManGame() : pacman({5, 5}) {
    maze = {{1,1,1,1,1,1,1,1},
            {1,2,2,0,2,2,2,1},
            {1,2,1,1,1,2,2,1},
            {1,2,1,0,1,2,2,1},
            {1,2,1,1,1,2,2,1},
            {1,2,2,2,2,2,2,1},
            {1,1,1,1,1,1,1,1}};

    ghosts.push_back(Ghost({6, 1}, Color(255, 0, 0))); 
    running = true;
}

void PacManGame::update(char direction) {
    pacman.move(direction, maze);
    for (auto &ghost : ghosts) {
        ghost.moveRandom(maze);
        if (ghost.position.x == pacman.position.x && ghost.position.y == pacman.position.y) {
            running = false;
            cout << "Pac-Man wurde gefangen! Spiel vorbei." << endl;
        }
    }
}

void drawGame(Canvas* canvas, PacManGame &game) {
    canvas->Clear();
    for (int y = 0; y < game.maze.size(); y++) {
        for (int x = 0; x < game.maze[y].size(); x++) {
            if (game.maze[y][x] == 1) draw_pixel(canvas, x, y, Color(0, 0, 255));
            if (game.maze[y][x] == 2) draw_pixel(canvas, x, y, Color(255, 255, 255));
        }
    }
    draw_pixel(canvas, game.pacman.position.x, game.pacman.position.y, game.pacman.color);
    for (auto &ghost : game.ghosts) {
        draw_pixel(canvas, ghost.position.x, ghost.position.y, ghost.color);
    }
}
