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
    typedef enum _BinaryTree::iter_order iter_order;
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {
    }

    ~BinaryTree() {
        // if (root != nullptr) {
        //     delete root;
        // }
    }

    BinaryTree &add_root(T root);
    BinaryTree &add_left(T parent, T item);

    BinaryTree &add_right(T parent, T item);

    iterator begin_preorder() {
        return iterator(iter_order::preorder, root);
    }

    iterator begin_postorder() {
        return iterator(iter_order::postorder, root);
    }

    iterator begin_inorder() {
        return iterator(iter_order::inorder, root);
    }

    iterator end_preorder() {
        return iterator(iter_order::preorder);
    }

    iterator end_postorder() {
        return iterator(iter_order::postorder);
    }

    iterator end_inorder() {
        return iterator(iter_order::inorder);
    }

    iterator begin() {
        // return &(m_first->m_value);
        return iterator{iter_order::inorder, root};
    }

    iterator end() {
        // return nullptr;
        return iterator{iter_order::inorder, nullptr};
    }

    friend std::ostream &operator<<(std::ostream &os, const BinaryTree &c) {
        return os;
    }
};
} // namespace ariel

#include "templates/BinaryTree.tpp"
