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
template <typename T, typename Y>
class TreeIterator {

protected:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    BinaryTreeNode *current;
    virtual void next(){
        //std::cout << "this should not be called" << endl;
    }; /* needs implementation */

public:
    //MyIterator(BinaryTreeNode *ptr = nullptr);

    // TreeIterator(const TreeIterator &old) {
    //     this->current = old.current;
    // }

    T &operator*() const {
        return this->current->m_value;
    }

    T *operator->() const {
        return &(this->current->m_value);
    }

    // a function that return *this from the inheriting class.
    virtual Y *cThis() {
        return nullptr;
    }

    // ++i;
    Y &operator++() {
        next();
        return *cThis();
    }

    const Y operator++(int) {
        Y tmp = *cThis();
        next();
        return tmp;
    }

    bool operator==(const TreeIterator &rhs) const {
        return this->current == rhs.current;
    }

    bool operator!=(const TreeIterator &rhs) const {
        return this->current != rhs.current;
    }

    //friend class ariel::BinaryTree<T>;
};
} // namespace _BinaryTree
} // namespace ariel