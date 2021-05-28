#pragma once

#include "templates/BinaryTreeInorderIterator.tpp"
//#include "templates/BinaryTreeIterator.tpp"
#include "templates/BinaryTreeNode.tpp"
#include "templates/BinaryTreePostorderIterator.tpp"
#include "templates/BinaryTreePreorderIterator.tpp"
#include <iostream>
#include <queue>

std::string addSpaces(int spaces) {
    std::string s;
    for (int i = 0; i < spaces; i++) {
        s += " ";
    }
    return s;
}

namespace ariel {
const int SPACE_NUM = 2;

template <typename T>
class BinaryTree {
private:
    typedef struct _BinaryTree::BinaryTreeNode<T> BinaryTreeNode;
    //typedef class _BinaryTree::iterator<T> iterator;
    typedef class _BinaryTree::Inorderiterator<T> inorder_iter;
    typedef class _BinaryTree::Postorderiterator<T> postorder_iter;
    typedef class _BinaryTree::Preorderiterator<T> preorder_iter;
    //typedef enum _BinaryTree::iter_order iter_order;
    BinaryTreeNode *root;

    void copy_tree(BinaryTreeNode &target, const BinaryTreeNode &source) {
        if (source.left != nullptr) {
            target.left = new BinaryTreeNode{source.left->m_value};
            copy_tree(*target.left, *source.left);
        }

        if (source.right != nullptr) {
            target.right = new BinaryTreeNode{source.right->m_value};
            copy_tree(*target.right, *source.right);
        }
    }

    int getDepth(BinaryTreeNode *node) const {
        if (node == nullptr) {
            return 0;
        }
        int l = getDepth(node->left);
        int r = getDepth(node->right);

        if (l >= r) {
            return 1 + l;
        }
        return 1 + r;
    }

public:
    BinaryTree() : root(nullptr) {
    }

    BinaryTree(const BinaryTree &tree) {
        root = new BinaryTreeNode{tree.root->m_value};
        copy_tree(*root, *tree.root);
    }

    BinaryTree(BinaryTree &&tree) noexcept {
        root = tree.root;
        tree.root = nullptr;
    }

    BinaryTree &operator=(const BinaryTree &tree) {
        if (this == &tree) {
            return *this;
        }
        if (root != nullptr) {
            delete root;
        }
        root = new BinaryTreeNode{tree.root->m_value};
        copy_tree(*root, *tree.root);
        return *this;
    }

    BinaryTree &operator=(BinaryTree &&tree) noexcept {
        if (root != nullptr) {
            delete root;
        }
        root = tree.root;
        tree.root = nullptr;
    }

    ~BinaryTree() {
        if (root != nullptr) {
            delete root;
        }
    }

    BinaryTree &add_root(T root);
    BinaryTree &add_left(T parent, T item);

    BinaryTree &add_right(T parent, T item);

    auto begin_preorder() {
        return preorder_iter{root};
        //return iterator(iter_order::preorder, root);
    }

    auto begin_postorder() {
        return postorder_iter{root};
        //return iterator(iter_order::postorder, root);
    }

    auto begin_inorder() {
        return inorder_iter{root};
        //return iterator(iter_order::inorder, root);
    }

    auto end_preorder() {
        return preorder_iter{};
        //return iterator(iter_order::preorder);
    }

    auto end_postorder() {
        return postorder_iter{};
        //return iterator(iter_order::postorder);
    }

    auto end_inorder() {
        return inorder_iter{};
        //return iterator(iter_order::inorder);
    }

    auto begin() {
        return begin_inorder();
        // return &(m_first->m_value);
        //return iterator{iter_order::inorder, root};
    }

    auto end() {
        return end_inorder();
        // return nullptr;
        // return iterator{iter_order::inorder, nullptr};
    }

    int getDepth() const {
        return getDepth(root);
    }

    friend std::ostream &operator<<(std::ostream &os, const BinaryTree &tree) {
        int depth = tree.getDepth();

        std::queue<BinaryTreeNode *> que;
        std::queue<BinaryTreeNode *> quen;

        int k = 1;
        for (int i = 0; i < depth; i++) {
            k *= 2;
        }

        quen.push(tree.root);
        while (quen.size() > 0) {
            os << std::endl;
            std::swap(quen, que);
            while (que.size() > 0) {
                BinaryTreeNode *current = que.front();

                que.pop();

                os << addSpaces(k * SPACE_NUM - 2);
                if (current != nullptr) {
                    os << current->m_value;
                    quen.push(current->left);
                    quen.push(current->right);
                } else {
                    os << addSpaces(2);
                }
                os << addSpaces(k * SPACE_NUM);
            }
            k /= 2;
        }

        return os;
    }
};
} // namespace ariel

#include "templates/BinaryTree.tpp"
