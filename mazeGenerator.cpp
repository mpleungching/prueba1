#include "MazeGenerator.h"
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>

// Constructor - matriz de nodos
MazeGenerator::MazeGenerator(int rows, int cols) : rows(rows), cols(cols) {
    maze = new Node*[rows];
    for (int i = 0; i < rows; ++i) {
        maze[i] = new Node[cols];
    }
    createMaze();
}

MazeGenerator::~MazeGenerator() {
    for (int i = 0; i < rows; ++i) {
        delete[] maze[i];
    }
    delete[] maze;
}

Node* MazeGenerator::getNode(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return &maze[row][col];
    }
    return nullptr;
}

// inicializar la matriz con paredes
void MazeGenerator::createMaze() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maze[i][j].setUp(nullptr);
            maze[i][j].setDown(nullptr);
            maze[i][j].setLeft(nullptr);
            maze[i][j].setRight(nullptr);
            maze[i][j].visited = false;
        }
    }

#ifdef USE_DFS
    generateMazeDFS(0, 0);
#elif defined(USE_BFS)
    generateMazeBFS(0, 0);
#endif
}

// DFS
void MazeGenerator::generateMazeDFS(int x, int y) {
    maze[x][y].visited = true;

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);

    for (auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;

        if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && !maze[nx][ny].visited) {
            if (dir == std::make_pair(-1, 0)) {
                maze[x][y].up = &maze[nx][ny];
                maze[nx][ny].down = &maze[x][y];
            } else if (dir == std::make_pair(1, 0)) {
                maze[x][y].down = &maze[nx][ny];
                maze[nx][ny].up = &maze[x][y];
            } else if (dir == std::make_pair(0, -1)) {
                maze[x][y].left = &maze[nx][ny];
                maze[nx][ny].right = &maze[x][y];
            } else if (dir == std::make_pair(0, 1)) {
                maze[x][y].right = &maze[nx][ny];
                maze[nx][ny].left = &maze[x][y];
            }

            generateMazeDFS(nx, ny);
        }
    }
}

// BFS
void MazeGenerator::generateMazeBFS(int x, int y) {
    std::queue<std::pair<int, int>> queue;
    queue.push({x, y});
    maze[x][y].visited = true;

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::random_device rd;
    std::mt19937 g(rd());

    while (!queue.empty()) {
        auto [cx, cy] = queue.front();
        queue.pop();

        std::shuffle(directions.begin(), directions.end(), g);

        for (auto& dir : directions) {
            int nx = cx + dir.first;
            int ny = cy + dir.second;

            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && !maze[nx][ny].visited) {

                if (dir == std::make_pair(-1, 0)) { // Arriba
                    maze[cx][cy].setUp(&maze[nx][ny]);
                    maze[nx][ny].setDown(&maze[cx][cy]);
                } else if (dir == std::make_pair(1, 0)) { // Abajo
                    maze[cx][cy].setDown(&maze[nx][ny]);
                    maze[nx][ny].setUp(&maze[cx][cy]);
                } else if (dir == std::make_pair(0, -1)) { // Izquierda
                    maze[cx][cy].setLeft(&maze[nx][ny]);
                    maze[nx][ny].setRight(&maze[cx][cy]);
                } else if (dir == std::make_pair(0, 1)) { // Derecha
                    maze[cx][cy].setRight(&maze[nx][ny]);
                    maze[nx][ny].setLeft(&maze[cx][cy]);
                }

                maze[nx][ny].visited = true;
                queue.push({nx, ny});
            }
        }
    }
}
