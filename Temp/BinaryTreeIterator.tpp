#pragma once
// #include "../BinaryTree.hpp"
#include "BinaryTreeNode.tpp"
#include <iostream>
#include <vector>

namespace ariel {

template <typename T>
class BinaryTree;

namespace _BinaryTree {

enum class iter_order {
    inorder,
    postorder,
    preorder,
};

template <typename T>
class iterator {

private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    std::vector<BinaryTreeNode *> path;
    BinaryTreeNode *current;
    unsigned int index = 0;

    void path_inorder(BinaryTreeNode *current, std::vector<BinaryTreeNode *> &path) {
        if (current != nullptr) {
            path_inorder(current->left, path);
            path.push_back(current);
            path_inorder(current->right, path);
        }
    }

    void path_postorder(BinaryTreeNode *current, std::vector<BinaryTreeNode *> &path) {
        if (current != nullptr) {
            path_postorder(current->left, path);
            path_postorder(current->right, path);
            path.push_back(current);
        }
    }

    void path_preorder(BinaryTreeNode *current, std::vector<BinaryTreeNode *> &path) {
        if (current != nullptr) {
            path.push_back(current);
            path_preorder(current->left, path);
            path_preorder(current->right, path);
        }
    }

public:
    iterator(iter_order order, BinaryTreeNode *ptr = nullptr) {
        path.clear();
        if (order == iter_order::inorder) {
            path_inorder(ptr, path);
        } else if (order == iter_order::postorder) {
            path_postorder(ptr, path);
        } else {
            path_preorder(ptr, path);
        }
        // so we can get to the end!
        path.push_back(nullptr);
        index = 0;
        current = path[index];
    }

    iterator(const iterator &copy) {
        this->index = copy.index;
        this->current = copy.current;
        this->path = copy.path;
    }

    T &operator*() const {
        return current->m_value;
    }

    T *operator->() const {
        return &(current->m_value);
    }

    // ++i;
    iterator &operator++() {
        index++;
        current = path[index];
        return *this;
    }

    const iterator operator++(int) {
        iterator tmp = *this;
        index++;
        current = path[index];
        return tmp;
    }

    bool operator==(const iterator &rhs) const {
        return current == rhs.current;
    }

    bool operator!=(const iterator &rhs) const {
        return current != rhs.current;
    }

    friend class ariel::BinaryTree<T>;
};
} // namespace _BinaryTree
} // namespace ariel