#pragma once

#include "templates/BinaryTreeIterator.tpp"
#include "templates/BinaryTreeNode.tpp"
#include <iostream>

namespace ariel {
template <typename T>
class BinaryTree {
private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    typedef class _BinaryTree::iterator<T> iterator;

public:
    BinaryTreeNode *root;

    BinaryTree() : root(nullptr) {
    }

    BinaryTree &add_root(T root);
    BinaryTree &add_left(T parent, T item);

    BinaryTree &add_right(T parent, T item);

    iterator begin_preorder() {
        return iterator();
    }

    iterator begin_postorder() {
        return iterator();
    }

    iterator begin_inorder() {
        return iterator();
    }

    iterator end_preorder() {
        return iterator();
    }

    iterator end_postorder() {
        return iterator();
    }

    iterator end_inorder() {
        return iterator();
    }

    iterator begin() {
        // return &(m_first->m_value);
        return iterator{nullptr};
    }

    iterator end() {
        // return nullptr;
        return iterator{nullptr};
    }

    friend std::ostream &operator<<(std::ostream &os, const BinaryTree &c) {
        return os;
    }
};
} // namespace ariel

#include "templates/BinaryTree.tpp"
