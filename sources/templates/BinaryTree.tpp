#pragma once
#include "../BinaryTree.hpp"
// #include "BinaryTreeIterator.tpp"
#include <iostream>

namespace ariel {

template <typename T>
BinaryTree<T> &BinaryTree<T>::add_root(T root) {
    if (this->root != nullptr) {
        this->root->m_value = root;
        //delete this->root;
    } else {
        this->root = new BinaryTreeNode{root};
    }
    return *this;
}

template <typename T>
BinaryTree<T> &BinaryTree<T>::add_left(T parent, T item) {
    //std::cout << (*this->begin_inorder()) == nullptr << std::endl;
    for (auto it = this->begin_inorder(); it != this->end_inorder(); ++it) {
        if ((*it) == parent) {
            BinaryTreeNode *p = it.current;
            if (p->left == nullptr) {
                p->left = new BinaryTreeNode{item};
            } else {
                p->left->m_value = item;
            }
            return *this;
        }
    } // prints: 4 2 5 1 3
    throw std::invalid_argument{"the parent value doesnt exist in the tree..."};
}

template <typename T>
BinaryTree<T> &BinaryTree<T>::add_right(T parent, T item) {
    for (auto it = this->begin_inorder(); it != this->end_inorder(); ++it) {
        if ((*it) == parent) {
            BinaryTreeNode *p = it.current;
            if (p->right == nullptr) {
                p->right = new BinaryTreeNode{item};
            } else {
                p->right->m_value = item;
            }
            return *this;
        }
    } // prints: 4 2 5 1 3
    throw std::invalid_argument{"the parent value doesnt exist in the tree..."};
} // namespace ariel

} // namespace ariel