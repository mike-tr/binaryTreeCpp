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

        pstack.push(nullptr);
        goLeft(ptr);
        this->current = pstack.top();
        pstack.pop();
        //std::cout << "done with ini" << std::endl;
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