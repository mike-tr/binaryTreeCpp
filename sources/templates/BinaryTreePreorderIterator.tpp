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
class Preorderiterator {
private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;

    std::stack<BinaryTreeNode *> pstack;
    BinaryTreeNode *current;

    void goNextNode() {
        pstack.pop();
        if (current->right != nullptr) {
            pstack.push(current->right);
        }
        if (current->left != nullptr) {
            pstack.push(current->left);
        }
        current = pstack.top();
    }

public:
    Preorderiterator(BinaryTreeNode *ptr = nullptr) {
        current = nullptr;
        if (ptr == nullptr) {
            current = nullptr;
            return;
        }

        pstack.push(nullptr);
        pstack.push(ptr);
        current = pstack.top();
        //std::cout << "done with ini : " << current->m_value << std::endl;
    }

    Preorderiterator(const Preorderiterator &copy) {
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
    Preorderiterator &operator++() {
        goNextNode();
        return *this;
    }

    const Preorderiterator operator++(int) {
        Preorderiterator tmp = *this;
        goNextNode();
        return tmp;
    }

    bool operator==(const Preorderiterator &rhs) const {
        return current == rhs.current;
    }

    bool operator!=(const Preorderiterator &rhs) const {
        return current != rhs.current;
    }

    friend class ariel::BinaryTree<T>;
};
} // namespace _BinaryTree
} // namespace ariel