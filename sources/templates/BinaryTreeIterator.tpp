#pragma once
//#include "../BinaryTree.hpp"
#include "templates/BinaryTreeNode.tpp"

namespace ariel {

namespace _BinaryTree {
template <typename T>
class iterator {

private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    BinaryTreeNode *pointer_to_current_node;

public:
    iterator(BinaryTreeNode *ptr = nullptr)
        : pointer_to_current_node(ptr) {
    }

    T &operator*() const {
        return pointer_to_current_node->m_value;
    }

    T *operator->() const {
        return &(pointer_to_current_node->m_value);
    }

    // ++i;
    iterator &operator++() {
        return *this;
    }

    const iterator operator++(int) {
        iterator tmp = *this;
        pointer_to_current_node = pointer_to_current_node->m_next;
        return tmp;
    }

    bool operator==(const iterator &rhs) const {
        return pointer_to_current_node == rhs.pointer_to_current_node;
    }

    bool operator!=(const iterator &rhs) const {
        return pointer_to_current_node != rhs.pointer_to_current_node;
    }
};
} // namespace _BinaryTree
} // namespace ariel