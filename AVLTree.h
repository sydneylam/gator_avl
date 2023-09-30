//
// Created by Sydney Lam
//

#pragma once
#include <vector>
#include "Node.h"
#include <string>

using namespace std;

class AVLTree
{
private:
    Node* root;
    int height(Node* root);

    Node* rotateLeft(Node *node);
    Node* rotateRight(Node *node);
    Node* rotateLeftRight(Node *node);
    Node* rotateRightLeft(Node *node);



    // helper functions
    int getBalance(Node *node);
    Node *minID(Node *node);


public:
    AVLTree();

    Node* insert(Node* root, string name, int id);
    Node *remove(Node *root, int id);
    Node* removeInOrder(Node* root, int nth);
    void inOrder(Node* root, vector<Node*> &nodesList);
    void preOrder(Node* root, vector<Node*> &nodesList);
    void postOrder(Node* root, vector<Node*> &nodesList);

    void printInOrder(Node* root);
    void printPreOrder(Node* root);
    void printPostOrder(Node* root);
    void printLevelCount(Node* root);

    bool searchName(Node* root, const string& name);
    Node *searchID(Node* root, int id);

    void setRoot(Node* _r) {root = _r;}
    Node* getRoot() {return this->root;}

};