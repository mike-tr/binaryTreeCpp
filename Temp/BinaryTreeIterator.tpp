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

enum class iter_order {
    inorder,
    postorder,
    preorder,
};

template <typename T>
class iterator {

private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    struct pathNode {
        BinaryTreeNode *src;
        bool seenLeft;
        bool seenRight;

        pathNode(BinaryTreeNode *src, bool seenLeft = false, bool seenRight = false) {
            this->src = src;
            this->seenLeft = seenLeft;
            this->seenRight = seenRight;
        }
    };
    std::vector<BinaryTreeNode *> path;
    std::stack<pathNode> pstack;
    BinaryTreeNode *current;
    bool lastLeft = false;

    unsigned int index = 0;

    void goLeft(BinaryTreeNode *src) {
        if (src == nullptr) {
            return;
        }
        pstack.emplace(pathNode{src, true, false});
        BinaryTreeNode *curr = src->left;
        while (curr != nullptr) {
            src = curr;
            pstack.emplace(pathNode{src, true, false});
            curr = src->left;
            pathNode n = pathNode{src, true, false};
        }
    }

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
        // path.clear();
        // if (order == iter_order::inorder) {
        //     path_inorder(ptr, path);
        // } else if (order == iter_order::postorder) {
        //     path_postorder(ptr, path);
        // } else {
        //     path_preorder(ptr, path);
        // }
        // // so we can get to the end!
        // path.push_back(nullptr);
        // index = 0;
        // current = path[index];

        current = nullptr;
        if (ptr == nullptr) {
            current = nullptr;
            return;
        }

        std::stack<pathNode> empty;
        pstack.swap(empty);
        // add empty node at start.
        if (order == iter_order::inorder) {
            goLeft(ptr);

        } else if (order == iter_order::postorder) {
            goLeft(ptr);
            pathNode top = pstack.top();

        } else {
            pstack.emplace(pathNode{ptr, false, false});
        }

        pathNode top = pstack.top();
        current = top.src;
        std::cout << "done with ini" << std::endl;
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
        // index++;
        // current = path[index];
        return *this;
    }

    const iterator operator++(int) {
        iterator tmp = *this;
        // index++;
        // current = path[index];
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