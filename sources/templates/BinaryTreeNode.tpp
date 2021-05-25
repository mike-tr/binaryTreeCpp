#pragma once

#include "../BinaryTree.hpp"

namespace ariel {

namespace _BinaryTree {
template <typename T>
struct BinaryTreeNode {
    BinaryTreeNode *left, *right, *parent;
    T m_value;
    BinaryTreeNode(const T &val) : m_value(val) {}
};
} // namespace _BinaryTree
} // namespace ariel
