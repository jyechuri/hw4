#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError
{
};

/**
 * A special kind of node for an AVL tree, which adds the balance as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key &key, const Value &value, AVLNode<Key, Value> *parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance() const;
    void setBalance(int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value> *getParent() const override;
    virtual AVLNode<Key, Value> *getLeft() const override;
    virtual AVLNode<Key, Value> *getRight() const override;

protected:
    int8_t balance_; // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class constructor
 */
template <class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key &key, const Value &value, AVLNode<Key, Value> *parent) : Node<Key, Value>(key, value, parent), balance_(0)
{
}

/**
 * A destructor which does nothing.
 */
template <class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{
}

/**
 * A getter for the balance of a AVLNode.
 */
template <class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
 * A setter for the balance of a AVLNode.
 */
template <class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
 * Adds diff to the balance of a AVLNode.
 */
template <class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value> *>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value> *>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template <class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value> *>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert(const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key &key);                              // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2);

    // Add helper functions here
    void rotateRight(AVLNode<Key, Value> *curr);
    void rotateLeft(AVLNode<Key, Value> *curr);

    // help with insert and remove
    void insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *curr);
    virtual void removeFix(AVLNode<Key, Value> *curr, int8_t diff);

    // helper that inherit search and predecessor
    AVLNode<Key, Value> *internalFind(const Key &key) const;
    static AVLNode<Key, Value> *predecessor(AVLNode<Key, Value> *current); // need to be static???????

    /*
        Node<Key, Value>* internalFind(const Key& k) const; // TODO
        static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
        static_cast<AVLNode<Key, Value>*>(this->predecessor(temp))
    */
};

template <class Key, class Value>
AVLNode<Key, Value> *AVLTree<Key, Value>::internalFind(const Key &key) const
{
    return (static_cast<AVLNode<Key, Value> *>(BinarySearchTree<Key, Value>::internalFind(key)));
}

template <class Key, class Value>
AVLNode<Key, Value> *AVLTree<Key, Value>::predecessor(AVLNode<Key, Value> *current)
{
    return (static_cast<AVLNode<Key, Value> *>(BinarySearchTree<Key, Value>::predecessor(current)));
}

// zig - zig
template <class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value> *curr)
{
    AVLNode<Key, Value> *currParent = curr->getParent();
    AVLNode<Key, Value> *currRside = curr->getRight();

    currRside->setParent(currParent);

    if (currParent == nullptr)
    {
        this->root_ = currRside;
    }
    // update it
    else if (currParent->getLeft() == curr)
    {
        currParent->setLeft(currRside);
    }
    else
    {
        currParent->setRight(currRside);
    }

    //  update everything else
    AVLNode<Key, Value> *currRchild = currRside->getLeft();
    currRside->setLeft(curr);
    curr->setParent(currRside);

    curr->setRight(currRchild);
    // avoid seg fault
    if (currRchild != nullptr)
    {
        currRchild->setParent(curr);
    }
}

// zig - zig -- same as left rotate function
template <class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value> *curr)
{
    // official left node
    AVLNode<Key, Value> *currParent = curr->getParent();
    AVLNode<Key, Value> *currLside = curr->getLeft();

    currLside->setParent(currParent);

    // set the new root ensure by using this!
    if (currParent == nullptr) 
    {
        this->root_ = currLside;
    }
    else if (currParent->getRight() == curr)
    {
        currParent->setRight(currLside);
    }
    else
    {
        currParent->setLeft(currLside);
    }
    // adjust the parents and children and nodes shift accordingly
    AVLNode<Key, Value> *currLchild = currLside->getRight();
    currLside->setRight(curr);
    curr->setParent(currLside);

    curr->setLeft(currLchild);
    // avoid seg fault
    if (currLchild != nullptr)
    {
        currLchild->setParent(curr);
    }
}

/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template <typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // create a new node
    AVLNode<Key, Value> *insertNode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);

    if (this->root_ == NULL)
    {
        this->root_ = insertNode;
        return;
    }

    // find item -- if it exists overwrite current value with the updated value
    // key exists
    if (internalFind(new_item.first) != nullptr)
    {
        internalFind(new_item.first)->setValue(new_item.second);
        delete insertNode;
        return;
    }

    AVLNode<Key, Value> *currNode = static_cast<AVLNode<Key, Value> *>(this->root_);

    while (true)
    {
        // go to the left if the insert data is less than
        if (new_item.first < currNode->getKey())
        {
            // check if anything is the the left, if not insert
            if (currNode->getLeft() == nullptr)
            {
                // make sure to update parent
                currNode->setLeft(insertNode);
                insertNode->setParent(currNode);
                break;
            }
            // keep going to the left
            else
            {
                currNode = currNode->getLeft();
            }
        }
        // check if needed to go to the right and the insert value is greater
        else
        {
            // insert to the right if nothing is there
            if (currNode->getRight() == nullptr)
            {
                currNode->setRight(insertNode);
                insertNode->setParent(currNode);
                break;
            }
            // keep going to the right
            else
            {
                currNode = currNode->getRight();
            }
        }
    }

        // CHECK IN SMALL LEVEL -- CURRNODE and INSERT NODE accounted for only
    // within the requirement of -1 or 1 and add element on either side then new balance = 0
    // only inserting to curr left or right side
    if (currNode->getBalance() == 1 || currNode->getBalance() == -1)
    {
        currNode->setBalance(0);
        return;
    }
    // adding item to either side will change the balance
    else if (currNode->getBalance() == 0)
    {
        // left side exists (right - left = 0-1 = -1)
        if (currNode->getLeft() == insertNode)
        {
            currNode->setBalance(-1);
        }
        else
        {
            // right - left = 1-0
            currNode->setBalance(1);
        }
        insertFix(currNode, insertNode);
    }
}

/*  
    parent -- referes to the inserted node parent
    curr -- referes to inserted node
*/

template <class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *curr)
{
    // BIG PICTURE -- CHECK ALL BALANCE FACTORS now
    // necessary steps for rebalancing -- zig-zig or zig-zag  --- insertFix(newNode, parent)
    // Edge case: nothing to rebalance
    if (parent == nullptr || parent->getParent() == nullptr)
    {
        return;
    }

    // continue with rotations -- grandparent
    AVLNode<Key, Value> *grand = parent->getParent();

    // check leftside first
    if (grand->getLeft() == parent)
    {
        // update the balance factor for everything else
        grand->updateBalance(-1);
        // exit if it's all balanced already
        if (grand->getBalance() == 0)
        {
            return;
        }
        else if (grand->getBalance() == -1)
        {
            insertFix(grand, parent);
            return;
        }
        //balance is -2
        else if (grand->getBalance() == -2)
        {
            // need to figure out which side the insertNode is
            if (parent -> getBalance() == -1) // zig-zig -- rotate right
            {
                rotateRight(grand);
                grand->setBalance(0);
                parent->setBalance(0);
            }
            else // zig-zag needed -- rotate left then right
            {
                rotateLeft(parent);
                rotateRight(grand);

                // check over inserted node -- is it balanced? to begin with
                if (curr->getBalance() == 0)
                {
                    grand->setBalance(0);
                    parent->setBalance(0);
                }
                // need example of this
                else if (curr->getBalance() == -1)
                {
                    grand->setBalance(1);
                    parent->setBalance(0);
                }
                else if (curr->getBalance() == 1)
                {
                    grand->setBalance(0);
                    parent->setBalance(-1);
                }
                curr->setBalance(0);
            }
        }
    }
    else 
    {
        // update the balance factor for everything else
        grand->updateBalance(1);
        // exit if it's all balanced now -- right side is also balanced
        if (grand->getBalance() == 0)
        {
            return;
        }
        else if (grand->getBalance() == 1)
        {
            insertFix(grand, parent);
            return;
        }
        else if (grand->getBalance() == 2)
        {
            // need to figure out which side the insertNode is
            if (parent -> getBalance() == 1) // zig-zig -- rotate rightparent->getRight() == curr
            {
                rotateLeft(grand);
                grand->setBalance(0);
                parent->setBalance(0);
            }
            else if (parent->getBalance() == -1) // zig-zag needed -- rotate left then right
            {
                rotateRight(parent);
                rotateLeft(grand);

                // check before the rotation occurs
                if (curr->getBalance() == 0)
                {
                    grand->setBalance(0);
                    parent->setBalance(0);
                }
                else if (curr->getBalance() == -1)
                {
                    grand->setBalance(0);
                    parent->setBalance(1);
                }
                // right is greater than left after rotation 
                else if (curr->getBalance() == 1)
                {
                    grand->setBalance(-1);
                    parent->setBalance(0);
                }
                curr->setBalance(0);
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */

template <class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value> *curr, int8_t diff) // Look at balance later
{
    // TODO
    // be aware of rotation and rebalance -- use predecessor

    // If curr is null, return
    if (curr == nullptr)
    { 
        return;
    }
    // Compute parent(node) and ndiff (for next recursive call)
    AVLNode<Key, Value> *currParent = curr->getParent();   
    int8_t ndiff;

    // same as remove but with ndiff
    if (currParent != nullptr)
    {
        // If removed node is left child of its parent, diff = +1
        if (currParent->getLeft() == curr)
        {
            ndiff = 1;
        }
        // If removed node is right child of its parent, diff = -1
        else
        {
            ndiff = -1;
        }
    }

    /*
        Case 1: balance(node) + diff == -/+ 2
            Check if zig-zig or zig-zag (choose rotations using “taller” of children) depending on balance of node’s child
            Perform rotation(s)
            Update balance of node, child, grandchild
            Call removeFix(parent, ndiff) accordingly
    */
   // similar to insert on LEFT SIDE
    if (curr -> getBalance() + diff == -2)
    {
        // finish this
        AVLNode<Key, Value>* currChild = curr -> getLeft();
        if (currChild->getBalance() == 0)
        {
            // zig - zig
            rotateRight(curr);
            currChild->setBalance(1);
            curr->setBalance(-1);
            return;
        }
        else if (currChild -> getBalance() == -1)
        {
            // zig-zig
            rotateRight(curr);
            currChild -> setBalance(0);
            curr -> setBalance (0);
            removeFix(currParent, ndiff);
        }
        else if (currChild -> getBalance() == 1)
        {
            // zig - zag
            AVLNode<Key, Value> *currGrand = currChild->getRight();
            rotateLeft(currChild);
            rotateRight(curr);

            if (currGrand -> getBalance() == 0)
            {
                curr -> setBalance(0);
                currChild->setBalance(0);
            }
            else if (currGrand -> getBalance() == -1)
            {
                curr -> setBalance(1);
                currChild->setBalance(0);
            }
            else if(currGrand -> getBalance() == 1)
            {
                curr -> setBalance(0);
                currChild->setBalance(-1);
            }
            currGrand -> setBalance(0);

            removeFix(currParent, ndiff);
        }
    }
    else if (curr-> getBalance() + diff == 2)
    {
        AVLNode<Key, Value> *currChild = curr->getRight();
        if (currChild->getBalance() == 0)
        {
            // zig - zig
            rotateLeft(curr);
            currChild->setBalance(-1);
            curr->setBalance(1);
            return;
        }
        else if (currChild->getBalance() == 1) // adjust the test
        {
            // zig-zig
            rotateLeft(curr);
            currChild->setBalance(0);
            curr->setBalance(0);
            removeFix(currParent, ndiff);
        }
        else if (currChild->getBalance() == -1)
        {
            // zig - zag
            AVLNode<Key, Value> *currGrand = currChild->getLeft();
            rotateRight(currChild);
            rotateLeft(curr);

            if (currGrand->getBalance() == 0)
            {
                curr->setBalance(0);
                currChild->setBalance(0);
            }
            else if (currGrand->getBalance() == -1)
            {
                curr->setBalance(0);
                currChild->setBalance(1);
            }
            else if (currGrand->getBalance() == 1)
            {
                curr->setBalance(-1);
                currChild->setBalance(0);
            }
            currGrand->setBalance(0);

            removeFix(currParent, ndiff);
        }
    }
    /*
        Case 2: balance(node) + diff == -/+ 1
            Update balance of node to -/+ 1
            DONE!
    */
    else if (curr -> getBalance() + diff == -1)
    {
        curr -> setBalance(-1);
        return;
    }
    else if(curr -> getBalance() + diff == 1)
    {
        curr ->setBalance(1);
        return;
    }
    /*
        Case 3: balance(node) + diff == 0
            Update balance of node to 0
            Call removeFix(parent, ndiff)
    */
    else if(curr -> getBalance() + diff == 0)
    {
        curr -> setBalance(0);
        removeFix(currParent, ndiff);
    }
}

template <class Key, class Value>
void AVLTree<Key, Value>::remove(const Key &key)
{
    // TODO
    if (this->root_ == nullptr)
    {
        return;
    }
    // check if item is found
    AVLNode<Key, Value> *currNode = internalFind(key);
    if (currNode == nullptr)
    {
        return;
    }

    /// check if item has 2 children -- get predecessor --> moce it to bottom
    if (currNode->getRight() != nullptr && currNode->getLeft() != nullptr)
    {
        AVLNode<Key, Value> *predNode = predecessor(currNode);
        nodeSwap(currNode, predNode);
    }
    // keep track of the parent value and its balance factor is tracked
    AVLNode<Key, Value> *currParent = currNode->getParent();
    int8_t diff = 0;

    if (currParent != nullptr)
    {
        // If removed node is left child of its parent, diff = +1
        if (currParent->getLeft() == currNode)
        {
            diff = 1;
        }
        // If removed node is right child of its parent, diff = -1
        else
        {
            diff = -1;
        }
    }
    // update all the pointers
    // no children exist
    if (currNode->getLeft() == nullptr && currNode->getRight() == nullptr)
    {
        // only one item
        if (currParent == nullptr)
        {
            // delete currNode
            this->root_ = nullptr;
        }
        // has a left child
        else if (currParent->getLeft() == currNode)
        {
            currParent->setLeft(nullptr);
        }
        // has only right child
        else
        {
            currParent->setRight(nullptr);
        }
    }
    // has one child to left
    if (currNode->getLeft() != nullptr && currNode->getRight() == nullptr)
    {
        // delete currNode and no parent exists
        if (currNode == this->root_)
        {
            this->root_ = currNode->getLeft();
        }
        // zig-sig
        else if (currParent->getLeft() == currNode)
        {
            currParent->setLeft(currNode->getLeft());
        }
        //zig-zag
        else
        {
            currParent->setRight(currNode->getLeft());
        }
        currNode->getLeft()->setParent(currParent);
    }
    // has one right child only
    else if (currNode->getLeft() == nullptr && currNode->getRight() != nullptr)
    {
        // delete currNode and no parent exists
        if (this->root_ == currNode)
        {
            this->root_ = currNode->getRight();
        }
        // zig - zag
        else if (currParent->getLeft() == currNode)
        {
            currParent->setLeft(currNode->getRight());
        }
        // zig - zig
        else
        {
            currParent->setRight(currNode->getRight());
        }
        currNode->getRight()->setParent(currParent);
    }
    // remove node and call recursive to fix
    delete currNode;
    removeFix(currParent, diff);
}

template <class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

#endif
