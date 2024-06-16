#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node();
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    bool visited;

    void setUp(Node* node);
    void setDown(Node* node);
    void setLeft(Node* node);
    void setRight(Node* node);
};

#endif // NODE_H
