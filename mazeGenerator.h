#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include "Node.h"
#include <stack>
#include <queue>
#include <unordered_map>

#define USE_DFS  // Cambia a #define USE_BFS para usar BFS

class MazeGenerator {
public:
    MazeGenerator(int rows, int cols);
    ~MazeGenerator();

    Node* getNode(int row, int col) const;
    void createMaze();

private:
    int rows;
    int cols;
    Node** maze;

    void generateMazeDFS(int x, int y);
    void generateMazeBFS(int x, int y);
};

#endif // MAZEGENERATOR_H
