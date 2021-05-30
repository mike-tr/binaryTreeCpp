#pragma once
// #include "../BinaryTree.hpp"
#include "BinaryTreeNode.tpp"
#include "TreeIterator.tpp"
#include <iostream>
#include <stack>
#include <vector>

namespace ariel {

template <typename T>
class BinaryTree;

namespace _BinaryTree {

template <typename T>
class Preorderiterator : public TreeIterator<T, Preorderiterator<T>> {
private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    std::stack<BinaryTreeNode *> pstack;

protected:
    // increment iterator method.
    // we traverse current, then left then right.
    void next() {
        if (this->current->right != nullptr) {
            pstack.push(this->current->right);
        }
        if (this->current->left != nullptr) {
            pstack.push(this->current->left);
        }
        this->current = pstack.top();
        pstack.pop();
    }

public:
    Preorderiterator(BinaryTreeNode *ptr = nullptr) {
        if (ptr == nullptr) {
            this->current = nullptr;
            return;
        }

        // set the last iter value to be nullptr
        pstack.push(nullptr);
        // the root of the tree is the starting value.
        this->current = ptr;
    }

    // this used as *this for the TreePointer
    Preorderiterator *cThis() {
        return this;
    }

    Preorderiterator(const Preorderiterator &copy) {
        this->pstack = copy.pstack;
        this->current = copy.current;
    }

    friend class ariel::BinaryTree<T>;
};
} // namespace _BinaryTree
} // namespace ariel