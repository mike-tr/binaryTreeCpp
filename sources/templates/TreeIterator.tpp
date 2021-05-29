#pragma once
// #include "../BinaryTree.hpp"
#include "BinaryTreeNode.tpp"
#include <iostream>
#include <stack>
#include <vector>

namespace ariel {

template <typename T>
class BinaryTree;

namespace _BinaryTree {

// Y is the typename of the inheriting object.
// T for the type of value we store in the tree.
template <typename T, typename cIterator>
class TreeIterator {

protected:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    BinaryTreeNode *current;
    virtual void next(){}; /* needs implementation */

public:
    // return the value of the node
    T &operator*() const {
        return this->current->m_value;
    }

    // the -> operator on the value of the node.
    T *operator->() const {
        return &(this->current->m_value);
    }

    // a function that return *this from the inheriting class.
    virtual cIterator *cThis() {
        return nullptr;
    }

    // ++i;
    cIterator &operator++() {
        next();
        return *cThis();
    }

    //i++;
    const cIterator operator++(int) {
        cIterator tmp = *cThis();
        next();
        return tmp;
    }

    TreeIterator kek() {
        return *this;
    }

    //is equal we care only about current iterator value.
    bool operator==(const TreeIterator &rhs) const {
        return this->current == rhs.current;
    }

    // same but neq.
    bool operator!=(const TreeIterator &rhs) const {
        return this->current != rhs.current;
    }
};
} // namespace _BinaryTree
} // namespace ariel