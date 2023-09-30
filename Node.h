//
// Created by Sydney Lam on 2/19/23.
//

#pragma once
#include <string>
using namespace std;

//Store student info, left and right children + constructor
struct Node
{
    string studentName;
    int gatorID;
    Node* left;
    Node* right;
    Node(string name, int id)
    {
        studentName = name;
        gatorID = id;
        left = nullptr;
        right = nullptr;
    }

    // helper functions
    bool isComplete(); // Has 2 two children
    bool hasLeft();    // Has ONLY a left child
    bool hasRight();   // Has ONLY a right child;
    bool isLeaf();     // Has NO kids.

};