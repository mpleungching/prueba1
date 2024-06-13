#ifndef NODE_H
#define NODE_H

#include <string>

template<typename T>
class Node {
private:
    T data;
public:
    Node(T data); // Constructor
    T getData(); // Getter
    void setData(T value); // Setter
};

// Implementación en el mismo archivo para evitar problemas de linkage
template<typename T>
Node<T>::Node(T data) : data(data) {}

template<typename T>
T Node<T>::getData() {
    return data;
}

template<typename T>
void Node<T>::setData(T value) {
    data = value;
}

#endif // NODE_H
