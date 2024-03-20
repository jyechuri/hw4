#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

bool checkChild(Node *curr)
{
    // check if node has children and if curr even exists
    return (curr && (curr->left || curr->right));
}

bool equalPaths(Node * root)
{
    // check if node is leaf -- does not have children then its equal
    if (!checkChild(root))
    {
        return true;
    } 

    // if both do not have a child on left and right subtree
    if (!checkChild(root->left) && !checkChild(root->right))
    {
        return true;
    }
    // uneven with the left and right child -- one points to something while the other is not
    else if (checkChild(root->left) != checkChild(root->right))
    {
        return false;
    }

    // Recursively check the left and right subtrees
    bool leftEqual = equalPaths(root->left);
    bool rightEqual = equalPaths(root->right);

    // Return true if the paths from leaves to the root are equal
    return (leftEqual == rightEqual);
}


