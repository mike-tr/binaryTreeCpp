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

template <typename T>
class Postorderiterator {

private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;

    std::stack<BinaryTreeNode *> pstack;
    BinaryTreeNode *current;

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

public:
    Postorderiterator(BinaryTreeNode *ptr = nullptr) {
        current = nullptr;
        if (ptr == nullptr) {
            current = nullptr;
            return;
        }

        pstack.push(nullptr);
        goDownwards(ptr);
        current = pstack.top();
        //std::cout << "done with ini : " << current->m_value << std::endl;
    }

    Postorderiterator(const Postorderiterator &copy) {
        this->pstack = copy.pstack;
        this->current = copy.current;
    }

    T &operator*() const {
        return current->m_value;
    }

    T *operator->() const {
        return &(current->m_value);
    }

    // ++i;
    Postorderiterator &operator++() {
        pstack.pop();
        BinaryTreeNode *curr = pstack.top();
        if (curr != nullptr && curr->left == current) {
            goDownwards(curr->right);
        }
        current = pstack.top();
        return *this;
    }

    const Postorderiterator operator++(int) {
        Postorderiterator tmp = *this;
        pstack.pop();
        BinaryTreeNode *curr = pstack.top();
        if (curr->left == current) {
            goDownwards(curr->right);
        }
        current = pstack.top();
        return tmp;
    }

    bool operator==(const Postorderiterator &rhs) const {
        return current == rhs.current;
    }

    bool operator!=(const Postorderiterator &rhs) const {
        return current != rhs.current;
    }

    friend class ariel::BinaryTree<T>;
};
} // namespace _BinaryTree
} // namespace ariel