//
// Created by Sydney Lam
//

#include <iostream>
#include "AVLTree.h"
#include <vector>
using namespace std;

AVLTree::AVLTree()
{
    root = nullptr;
}

//Helper Functions
bool Node::isComplete() { return ((this->left != nullptr) && (this->right != nullptr)); }
bool Node::hasLeft() { return ((this->left != nullptr) && (this->right == nullptr)); }
bool Node::hasRight() { return ((this->left == nullptr) && (this->right != nullptr)); }
bool Node::isLeaf() { return ((this->left == nullptr) && (this->right == nullptr)); }

int AVLTree::getBalance(Node *n)
{
    if (n == nullptr)
        return 0;
    else if (n->isLeaf())
        return 0;
    else if (n->isComplete())
        return height(n->left) - height(n->right);
    else if (n->hasLeft())
        return height(n->left);
    else if (n->hasRight())
        return height(n->right) * -1;
    else
        return 0;
}

//-------HEIGHT------- (Website Digital Ocean - "Height of a binary tree tutorial"):
int AVLTree::height(Node *root)
{
    if (root == nullptr)
        return 0;
    else
    {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        // Returning the length of the longest path from the root node
        if (leftHeight >= rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
}

//-------ROTATIONS------- (All from STEPIK 5.1b)

Node *AVLTree::rotateLeft(Node *node)
{
    Node *rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    return rightChild;
}

Node *AVLTree::rotateRight(Node *node)
{
    Node *leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    return leftChild;
}

//-------INSERTION-------:

// Regular BST insertion (STEPIK PROBLEM 4.3)
Node *AVLTree::insert(Node *root, string name, int id)
{
    if (root == nullptr)
    {
        root = new Node(name, id);
        return root;
    }
    else if (id < root->gatorID)
        root->left = insert(root->left, name, id);
    else if (id > root->gatorID)
        root->right = insert(root->right, name, id);
    else
    { // duplicate ID
        cout << "unsuccessful" << endl;
        return root;
    }

    // balance tree
    int balRoot = getBalance(root);
    int balL = getBalance(root->left);
    int balR = getBalance(root->right);

    // left left case
    if (balRoot == 2 && balL == 1)
        return rotateRight(root);
        // right right case
    else if (balRoot == -2 && balR == -1)
        return rotateLeft(root);
        // left right case
    else if (balRoot == 2 && balL == -1)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
        // right left case
    else if (balRoot == -2 && balR == 1)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

//-------REMOVAL-------

Node *AVLTree::remove(Node *root, int id)
{
    // null check
    Node *temp = searchID(root, id);
    if (!temp)
    {
        cout << "unsuccessful" << endl;
        return nullptr;
    }

    if (!root)
        return root;
    if (id < root->gatorID)
        root->left = remove(root->left, id);
    else if (id > root->gatorID)
        root->right = remove(root->right, id);
    else
    {
        // Node has 1 or 0 children
        if (root->isLeaf())
        {
            cout << "successful" << endl;
            return nullptr;
        }
        else if (root->hasRight())
        {
            Node *temp = root->right;
            cout << "successful" << endl;
            free(root);
            return temp;
        }
        else if (root->hasLeft())
        {
            Node *temp = root->left;
            cout << "successful" << endl;
            free(root);
            return temp;
        }
        else // Node has 2 children
        {
            Node *temp = minID(root->right);
            root->gatorID = temp->gatorID;
            root->studentName = temp->studentName;
            root->right = remove(root->right, root->gatorID);
        }
        return root;
    }
    return root;
}

// Returns the smallest node in tree; used in deletion of node with two children. O(h) where h is the height, time complexity.
Node *AVLTree::minID(Node *node)
{
    Node *curr = node;
    if (curr == nullptr)
        return nullptr;
    while (curr->left != nullptr)
        curr = curr->left;
    return curr;
}

//removeInOrder N
Node* AVLTree::removeInOrder(Node* root, int nth)
{

    vector<Node*> accounts;
    inOrder(root, accounts);

    if (nth > accounts.size()-1) {
        cout << "unsuccessful" << endl;
    }
    else {
        remove(root, accounts[nth]->gatorID);
    }
    return root;
}

//-------TRAVERSALS-------:

// Inorder Traversal (STEPIK 4.2)
void AVLTree::inOrder(Node *root, vector<Node *> &nodesList)
{
    // Adds nodes into nodes list in inOrder fashion LNR
    if (root == nullptr)
        return;
    inOrder(root->left, nodesList);
    nodesList.push_back(root);
    inOrder(root->right, nodesList);
}

// PreOrder Traversal
void AVLTree::preOrder(Node *root, vector<Node *> &nodesList)
{
    // Adds nodes into nodes list in preOrder fashion NLR
    if (root == nullptr)
        return;
    nodesList.push_back(root);
    preOrder(root->left, nodesList);
    preOrder(root->right, nodesList);
}

// PostOrder Traversal
void AVLTree::postOrder(Node *root, vector<Node *> &nodesList)
{
    // Adds nodes into nodes list in postOrder fashion LRN
    if (root == nullptr)
        return;

    postOrder(root->left, nodesList);
    postOrder(root->right, nodesList);
    nodesList.push_back(root);
}

//-------PRINTING-------

// Print InOrder
void AVLTree::printInOrder(Node *root)
{
    vector<Node *> accounts;
    string name;

    // Call inOrder function to add all nodes to vector accounts in inOrder fashion
    inOrder(root, accounts);

    for (int i = 0; i < accounts.size(); i++)
    {
        //giving a variable to current name so removing quotations is easier
        name = accounts[i]->studentName;

        // special case for last account name (no comma)
        if (i == accounts.size() - 1)
            cout << name.substr(1,name.length()-2) << endl;
        else
            cout << name.substr(1,name.length()-2) << ", ";
    }
}

// Print PreOrder
void AVLTree::printPreOrder(Node *root)
{
    vector<Node *> accounts;
    string name;

    // Call preOrder function to add all nodes to vector accounts in preOrder fashion
    preOrder(root, accounts);

    for (int i = 0; i < accounts.size(); i++)
    {
        //giving a variable to current name so removing quotations is easier
        name = accounts[i]->studentName;

        // special case for last account name (no comma)
        if (i == accounts.size() - 1)
            cout << name.substr(1,name.length()-2) << endl;
        else
            cout << name.substr(1,name.length()-2) << ", ";
    }
}

// Print PostOrder
void AVLTree::printPostOrder(Node *root)
{
    vector<Node *> accounts;
    string name;

    // Call postOrder function to add all nodes to vector accounts in postOrder fashion
    //(Website: StackOverflow - "When to use Preorder, Postorder, and Inorder Binary Search Tree Traversal strategies"
    postOrder(root, accounts);

    for (int i = 0; i < accounts.size(); i++)
    {
        //giving a variable to current name so removing quotations is easier
        name = accounts[i]->studentName;

        // special case for last account name (no comma)
        if (i == accounts.size() - 1)
            cout << name.substr(1,name.length()-2) << endl;
        else
            cout << name.substr(1,name.length()-2) << ", ";
    }
}

// Print Levels (print height)
void AVLTree::printLevelCount(Node *root)
{
    cout << height(root) << endl;
}

//-------SEARCHING-------:

// Searching for a name to return IDs
bool AVLTree::searchName(Node *root, const string& name)
{
    vector<Node *> accounts;
    // filling a vector named accounts with a copy of the tree through preOrder traversal
    preOrder(root, accounts);
    // flag to indicate if name was found or not in the vector

    bool foundName = false;

    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return false;
    }

    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i]->studentName == name)
        {
            cout << accounts[i]->gatorID << endl;
            foundName = true;
        }
    }

    if (!foundName) {
        cout << "unsuccessful" << endl;
    }

}

// Searching for an ID to return a name
Node *AVLTree::searchID(Node *root, int id)
{
    vector<Node *> accounts;
    // filling a vector named accounts with a copy of the tree through preOrder traversal
    preOrder(root, accounts);
    // flag to indicate if ID was found or not in the vector
    bool foundID = false;

    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    }


    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i]->gatorID == id)
        {
            return accounts[i];
        }
    }

    if (foundID == false) {
        cout << "unsuccessful" << endl;
        return nullptr;
    }

}
