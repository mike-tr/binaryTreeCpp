#pragma once

#include "../BinaryTree.hpp"

namespace ariel {

namespace _BinaryTree {

template <typename T>
struct BinaryTreeNode {
    BinaryTreeNode *left, *right, *parent;
    T m_value;
    BinaryTreeNode(const T &val) : m_value(val), parent(nullptr), left(nullptr), right(nullptr) {}

    ~BinaryTreeNode() {
        //std::cout << "destroyed : " << m_value << std::endl;
        // destroy all nodes downwards
        if (right != nullptr) {
            delete right;
        }
        if (left != nullptr) {
            delete left;
        }
    }
};
} // namespace _BinaryTree
} // namespace ariel
