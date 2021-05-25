#pragma once
#include "../BinaryTree.hpp"
#include <iostream>

namespace ariel {

template <typename T>
BinaryTree<T> &BinaryTree<T>::add_root(T root) {
    BinaryTreeNode node{root};
    return *this;
}

template <typename T>
BinaryTree<T> &BinaryTree<T>::add_left(T parent, T item) {
    return *this;
}

template <typename T>
BinaryTree<T> &BinaryTree<T>::add_right(T parent, T item) {
    return *this;
} // namespace ariel
} // namespace ariel