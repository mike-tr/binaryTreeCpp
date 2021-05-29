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
class Postorderiterator : public TreeIterator<T, Postorderiterator<T>> {

private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    std::stack<BinaryTreeNode *> pstack;

    void goDownwards(BinaryTreeNode *cnode) {
        // get to the left most leaf.
        // that is go as much left, and right if possible.
        while (cnode != nullptr) {
            pstack.emplace(cnode);
            BinaryTreeNode *curr = cnode->left;
            while (curr != nullptr) {
                cnode = curr;
                pstack.emplace(cnode);
                curr = cnode->left;
            }
            cnode = cnode->right;
        }
    }

protected:
    // increment iterator method.
    void next() {
        BinaryTreeNode *curr = pstack.top();
        if (curr != nullptr && curr->left == this->current) {
            goDownwards(curr->right);
        }
        this->current = pstack.top();
        pstack.pop();
    }

public:
    Postorderiterator(BinaryTreeNode *ptr = nullptr) {
        if (ptr == nullptr) {
            this->current = nullptr;
            return;
        }

        pstack.push(nullptr);
        goDownwards(ptr);
        this->current = pstack.top();
        pstack.pop();
        //std::cout << "done with ini : " << current->m_value << std::endl;
    }

    Postorderiterator(const Postorderiterator &copy) {
        this->pstack = copy.pstack;
        this->current = copy.current;
    }

    // this used as *this for the TreePointer
    Postorderiterator *cThis() {
        return this;
    }

    friend class ariel::BinaryTree<T>;
};
} // namespace _BinaryTree
} // namespace ariel