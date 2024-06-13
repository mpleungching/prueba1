#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>

template<typename T>
class Graph {
private:
    std::unordered_map<Node<T>*, std::list<Node<T>*>> adjLists;
    bool directed;
public:
    Graph(bool isDirected = false) : directed(isDirected) {}
    void addNode(Node<T>* node);  // To add nodes explicitly if needed
    void addEdge(Node<T>* src, Node<T>* dest);
    void DFS(Node<T>* startVertex);
    void BFS(Node<T>* startVertex);
};

// Implementación en el mismo archivo para evitar problemas de linkage
template<typename T>
void Graph<T>::addNode(Node<T>* node) {
    if (adjLists.find(node) == adjLists.end()) {
        adjLists[node] = std::list<Node<T>*>();
    }
}

template<typename T>
void Graph<T>::addEdge(Node<T>* src, Node<T>* dest) {
    addNode(src);
    addNode(dest);
    adjLists[src].push_back(dest);
    if (!directed) {
        adjLists[dest].push_back(src);
    }
}

template<typename T>
void Graph<T>::DFS(Node<T>* startVertex) {
    std::unordered_map<Node<T>*, bool> visited;
    std::stack<Node<T>*> stack;
    stack.push(startVertex);

    while (!stack.empty()) {
        Node<T>* vertex = stack.top();
        stack.pop();

        if (!visited[vertex]) {
            std::cout << vertex->getData() << " ";
            visited[vertex] = true;
        }

        for (auto it = adjLists[vertex].rbegin(); it != adjLists[vertex].rend(); ++it) {
            if (!visited[*it]) {
                stack.push(*it);
            }
        }
    }
}

template<typename T>
void Graph<T>::BFS(Node<T>* startVertex) {
    std::unordered_map<Node<T>*, bool> visited;
    std::queue<Node<T>*> queue;
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        Node<T>* vertex = queue.front();
        queue.pop();
        std::cout << vertex->getData() << " ";

        for (Node<T>* neighbor : adjLists[vertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }
}

// Explicita la instancia de plantilla para evitar errores de linkage
template class Graph<int>;
template class Graph<std::string>;

#endif // GRAPH_H
