#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value> *successor(Node<Key, Value> *current);
    // isBalanced Helpter
    bool isBalancedHelper(Node<Key, Value> *curr) const;
    int getHeight(Node<Key, Value> *temp) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (current_ != rhs.current_);

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    // inorder --- lnr -- successor
    current_ = successor(current_);
    return *this;

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    // if empty add the root node and leave
    if (root_ == nullptr)
    {
        // new node = Node( key, value, parent);
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        return;
    }
    // find item -- if it exists overwrite current value with the updated value
    // key exists
    if (internalFind(keyValuePair.first))
    {
        internalFind(keyValuePair.first)->setValue(keyValuePair.second);
        return;
    }
    // add accordingly
    Node<Key, Value> *currNode = root_;
    // Node<Key, Value> *insertNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, currNode);

    while (currNode != nullptr)
    {
        // go to the left if the insert data is less than
        if (keyValuePair.first < currNode -> getKey())
        {
            // check if anything is the the left, if not insert
            if (currNode -> getLeft() == nullptr)
            {
                // make sure to update parent
                Node<Key, Value> *insertNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, currNode);
                currNode->setLeft(insertNode);
                return;
            }
            // keep going to the left
            else
            {
                currNode = currNode -> getLeft();
            }
        }
        // check if needed to go to the right and the insert value is greater
        else
        {
            // insert to the right if nothing is there
            if (currNode -> getRight() == nullptr)
            {
                Node<Key, Value> *insertNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, currNode);
                currNode->setRight(insertNode);
                return;
            }
            // keep going to the right
            else
            {
                currNode = currNode -> getRight();
            }
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // check if key even exists
    Node<Key, Value> *findNode = internalFind(key);

    // tree does not exists or node is not found in
    if (root_ == nullptr || findNode == nullptr)
    {
        return;
    }

    // remove root with 2 children 

    // two children -- swap with PREDECESSOR -- then becomes case with 0 or 1 children
    if (findNode->getLeft() != nullptr && findNode->getRight() != nullptr)
    {
        Node<Key, Value> *predNode = predecessor(findNode);
        nodeSwap(findNode, predNode);
        if (findNode == root_)
        {
            root_ = predNode;
        }
        
    }

    // leaf node -- no children 
    // or write as !findNode -> getLeft()
    if (findNode -> getLeft() == nullptr && findNode -> getRight() == nullptr)
    {
        // only one node exists (root)- nothing above so set everything to null
        // checking leaf
        if (findNode -> getParent() == nullptr)
        {
            root_ = nullptr;
        }
        // always check left before right -- delete the leaf and make it null
        else if(findNode -> getParent() -> getLeft() == findNode)
        {
            // set the left to nothing now that findNode is taken out
            findNode->getParent() -> setLeft(nullptr);
        }
        else
        {
            // same thing for the right case
            findNode->getParent() -> setRight(nullptr);
        }
        delete findNode;
        return;
    }

    // one child
    // onle one child exists
    else if (findNode -> getLeft() != nullptr || findNode -> getRight() != nullptr)
    {
        Node<Key, Value> *parent = findNode -> getParent();
        // see if the findNode is a root and parent 
        if (parent == nullptr)
        {
            // check the left side and set right side as root
            if (findNode -> getLeft() == nullptr)
            {
                findNode -> getRight() -> setParent(nullptr);
                root_ = findNode -> getRight();
            }
            // check the right side and set left as root
            else if (findNode -> getRight() == nullptr)
            {
                findNode -> getLeft() -> setParent(nullptr);
                root_ = findNode -> getLeft();
            }
            delete findNode;
        }

        // findNode is the left child of the parent
        else if (findNode -> getParent() -> getLeft() == findNode)
        {
            // node is left child
            if (findNode -> getRight() == nullptr)
            {
                // adjust direction in both ways
                parent -> setLeft(findNode->getLeft());
                findNode -> getLeft() -> setParent (parent);
            }
            // node is right child
            else if (findNode -> getLeft() == nullptr)
            {
                parent -> setLeft(findNode->getRight());
                findNode -> getRight() -> setParent(parent);
            }

            delete findNode;
        }

        // findNode is thr right child of parent
        else if (findNode -> getParent() -> getRight() == findNode)
        {
            // node is left
            /*
            all above 
                20 
                  \
                   25 (x)
                   /OR\      
                  24   30
            */
            if (findNode -> getRight() == nullptr)
            {
                parent -> setRight(findNode -> getLeft());
                findNode -> getLeft() -> setParent(parent);
            }
            else if (findNode->getLeft() == nullptr)
            {
                parent->setRight(findNode->getRight());
                findNode->getRight()->setParent(parent);
            }
            delete findNode;
        }
    }
    
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // keep track of the predecessor

    // N has a left child. predecessor = rightmost element of N's left subtree.
    // left side exists (2,5,6,7,8,15,20) -- 6 pred = 5
    if (current -> getLeft())
    {
        current = current -> getLeft();
        // if right side exists
        while (current -> getRight())
        {
            current = current -> getRight();
        }
        return current;
    }
    // N does not have a left child, and there are no rightward or at least 1
    // step along the path to it from the root.
    // for leaf nodes
    else
    {
        Node<Key, Value> * parent = current -> getParent();
        // located on left side of parent -- goo up tre to prev parent of current parent 
        while (parent != nullptr && (current == parent -> getLeft())) 
        {
            current = parent;
            parent = current -> getParent();
        }
        return parent;
    }
}

template <class Key, class Value>
Node<Key, Value> *
BinarySearchTree<Key, Value>::successor(Node<Key, Value> *current)
{
    // TODO
    // keep track of the successor -- similar to predecessor
    if (current -> getRight())
    {
        current = current -> getRight();
        while (current->getLeft())
        {
            current = current ->getLeft();
        }
        return current;
    }
    else
    {
        Node<Key, Value> *parent = current->getParent();
        while (parent != nullptr && (current == parent->getRight()))
        {
            current = parent;
            parent = current -> getParent();
        }
        return parent;
    }
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    while (root_ != nullptr)
    {
        // reset all key values
        remove(root_->getKey());
    }
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // just like storing min -- always on left
    Node<Key, Value> *smallest = root_;
    Node<Key, Value> *iterate = root_;

    // keep going to the left, where the smallest number exists
    while (iterate != nullptr)
    {
        if (iterate->getLeft() != nullptr)
        {
            smallest = iterate;
        }
        iterate = iterate->getLeft();
    }
    // return smallest value
    return smallest;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value> *foundNode = root_;
    // same as searching through BST
    // nothing
    while (true) // or change to foundNode != nullptr
    {
        // either found the item or it is nullptr then return the key
        if (foundNode == nullptr || foundNode->getKey() == key)
        {
            return foundNode;
        }
        // go to right if current is less than what you want to search for
        if (foundNode->getKey() < key)
        {
            foundNode = foundNode->getRight();
        }
        // go left if current is creater than what you are searching
        else
        {
            foundNode = foundNode->getLeft();
        }
    }   
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    // call the helper functions to do the work
    return isBalancedHelper(root_);
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value> *curr) const
{
    if (curr == nullptr)
    {
        return true;
    }

    int leftH = getHeight(curr->getLeft());
    int rightH = getHeight(curr->getRight());
    int balanceFactor = rightH - leftH;

    if (abs(balanceFactor) <= 1 && isBalancedHelper(curr->getLeft()) && isBalancedHelper(curr->getRight()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value> *temp) const
{
    if (temp == nullptr)
    {
        return -1;
    }
    // only root exists
    if (temp->getLeft() == nullptr && temp->getRight() == nullptr)
    {
        return 0;
    }

    int leftHeight = getHeight(temp->getLeft());
    int rightHeight = getHeight(temp->getRight());

    // increment height everytime after recursion
    if (leftHeight > rightHeight)
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
    return 0;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
