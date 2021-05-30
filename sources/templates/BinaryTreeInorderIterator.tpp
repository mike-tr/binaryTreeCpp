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
class Inorderiterator : public TreeIterator<T, Inorderiterator<T>> {

private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;

    std::stack<BinaryTreeNode *> pstack;
    //BinaryTreeNode *current;

    void goLeft(BinaryTreeNode *cnode) {
        if (cnode == nullptr) {
            return;
        }
        pstack.emplace(cnode);
        BinaryTreeNode *curr = cnode->left;
        while (curr != nullptr) {
            cnode = curr;
            pstack.emplace(cnode);
            curr = cnode->left;
        }
    }

protected:
    // increment iterator method.
    // when we are done with a node, we check if it has a right child
    // if there is one, find its most left child and go there.
    void next() {
        goLeft(this->current->right);
        this->current = pstack.top();
        pstack.pop();
    }

public:
    Inorderiterator(BinaryTreeNode *ptr = nullptr) {
        if (ptr == nullptr) {
            this->current = nullptr;
            return;
        }

        // set the last "value" to be nullptr
        pstack.push(nullptr);

        // find the left most node and set the iterator to point to it.
        goLeft(ptr);
        this->current = pstack.top();
        pstack.pop();
    }

    Inorderiterator(const Inorderiterator &copy) {
        this->pstack = copy.pstack;
        this->current = copy.current;
    }

    // this used as *this for the TreePointer
    Inorderiterator *cThis() {
        return this;
    }

    friend class ariel::BinaryTree<T>;
};
} // namespace _BinaryTree
} // namespace ariel