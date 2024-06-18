#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <random>

// graph.h
template <typename T>
class Node {
public:
    T value;
    Node(T val) : value(val) {}
};

template <typename T>
class Graph {
public:
    std::unordered_map<Node<T>*, std::list<Node<T>*>> adjLists;

    void addEdge(Node<T>* u, Node<T>* v) {
        adjLists[u].push_back(v);
        adjLists[v].push_back(u);
    }

    // This function removes the edge between two nodes
    void removeEdge(Node<T>* u, Node<T>* v) {
        adjLists[u].remove(v);
        adjLists[v].remove(u);
    }
};

// maze.h
class Cell {
public:
    int x, y;
    bool visited;
    bool walls[4];

    Cell(int x, int y) : x(x), y(y), visited(false) {
        walls[0] = walls[1] = walls[2] = walls[3] = true;
    }
};

class Maze {
public:
    int width, height;
    std::vector<std::vector<Cell>> cells;

    Maze(int width, int height) : width(width), height(height), cells(width, std::vector<Cell>(height, Cell(0, 0))) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                cells[i][j] = Cell(i, j);
            }
        }
    }

    void removeWall(Cell &current, Cell &next) {
        int dx = next.x - current.x;
        int dy = next.y - current.y;

        if (dx == 1) {
            current.walls[1] = false;
            next.walls[3] = false;
        } else if (dx == -1) {
            current.walls[3] = false;
            next.walls[1] = false;
        }

        if (dy == 1) {
            current.walls[2] = false;
            next.walls[0] = false;
        } else if (dy == -1) {
            current.walls[0] = false;
            next.walls[2] = false;
        }
    }

    void printMaze() {
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                std::cout << "+";
                if (cells[i][j].walls[0]) {
                    std::cout << "---";
                } else {
                    std::cout << "   ";
                }
            }
            std::cout << "+" << std::endl;

            for (int i = 0; i < width; ++i) {
                if (cells[i][j].walls[3]) {
                    std::cout << "|";
                } else {
                    std::cout << " ";
                }

                std::cout << "   ";
            }
            std::cout << "|" << std::endl;
        }

        for (int i = 0; i < width; ++i) {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
    }
};

const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

void generateMazeDFS(Maze &maze, int startX, int startY) {
    std::stack<Cell*> stack;
    stack.push(&maze.cells[startX][startY]);
    maze.cells[startX][startY].visited = true;

    while (!stack.empty()) {
        Cell* current = stack.top();
        stack.pop();

        std::vector<std::pair<int, int>> neighbors;
        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (nx >= 0 && nx < maze.width && ny >= 0 && ny < maze.height && !maze.cells[nx][ny].visited) {
                neighbors.push_back({nx, ny});
            }
        }

        if (!neighbors.empty()) {
            stack.push(current);

            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(neighbors.begin(), neighbors.end(), g);

            auto [nx, ny] = neighbors.front();
            maze.cells[nx][ny].visited = true;
            maze.removeWall(*current, maze.cells[nx][ny]);
            stack.push(&maze.cells[nx][ny]);
        }
    }
}

int main() {
    int width = 5;
    int height = 5;
    Maze maze(width, height);

    generateMazeDFS(maze, 0, 0);

    maze.printMaze();

    return 0;
}
