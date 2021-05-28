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
class Inorderiterator {

private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;

    std::stack<BinaryTreeNode *> pstack;
    BinaryTreeNode *current;

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

public:
    Inorderiterator(BinaryTreeNode *ptr = nullptr) {
        current = nullptr;
        if (ptr == nullptr) {
            current = nullptr;
            return;
        }

        pstack.push(nullptr);
        goLeft(ptr);
        current = pstack.top();
        //std::cout << "done with ini" << std::endl;
    }

    Inorderiterator(const Inorderiterator &copy) {
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
    Inorderiterator &operator++() {
        pstack.pop();
        goLeft(current->right);
        current = pstack.top();
        return *this;
    }

    const Inorderiterator operator++(int) {
        Inorderiterator tmp = *this;
        pstack.pop();
        goLeft(current->right);
        current = pstack.top();
        return tmp;
    }

    bool operator==(const Inorderiterator &rhs) const {
        return current == rhs.current;
    }

    bool operator!=(const Inorderiterator &rhs) const {
        return current != rhs.current;
    }

    friend class ariel::BinaryTree<T>;
};
} // namespace _BinaryTree
} // namespace ariel