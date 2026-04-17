/**
* ---------------------------------------------------------------------------*
 * | File Name   : ShawarebBinaryTree.h                                      |*
 * |                                                                         |*
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |*
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Binary Tree implementation for Data Structures.           |*
 * ---------------------------------------------------------------------------*
**/

#ifndef SHAWAREB_BINARY_TREE
#define SHAWAREB_BINARY_TREE

#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template<typename T>
// Node for binary tree with left and right child pointers
struct Node {
    T data{};
    Node<T> *right{};
    Node<T> *left{};

    Node(T data) : data(data) {
    }

    ~Node() {
        cout << "Destroy value: " << data << " at address: " << this << endl;
    }
};

template<typename T>
// Binary tree implementation with various traversal operations
class ShawarebBinaryTree {
private:
  Node<T> *root;

  // Time: O(n), Space: O(n)
  // Recursively copies entire tree structure
  void copy_tree(Node<T> * &copiedTreeRoot, Node<T> *otherTreeRoot) {
        if (!otherTreeRoot) {
            copiedTreeRoot = nullptr;
            return;
        } else {
            copiedTreeRoot = new Node<T>(otherTreeRoot->data);
            copy_tree(copiedTreeRoot->right, otherTreeRoot->right);
            copy_tree(copiedTreeRoot->left, otherTreeRoot->left);
        }
    }

  // Time: O(n), Space: O(n)
  // Recursively deallocates all nodes
  void destroy(Node<T> * &node) {
        if (!node) return;

        destroy(node->left);
        destroy(node->right);
        delete node;
        node = nullptr;
    }

  // Time: O(n), Space: O(n)
  // In-order traversal: left, root, right
  void inorder(Node<T> *node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

  // Time: O(n), Space: O(n)
  // Pre-order traversal: root, left, right
  void preorder(Node<T> *node) const {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

  // Time: O(n), Space: O(n)
  // Post-order traversal: left, right, root
  void postorder(Node<T> *node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

  // Time: O(n), Space: O(n)
  int height(Node<T> *node) const {
        if (!node) return 0;

        return max(height(node->left) + 1, height(node->right) + 1);
    }

  // Time: O(n), Space: O(n)
  int count_leaves(Node<T> *node) const {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;

        return count_leaves(node->left) + count_leaves(node->right);
    }

  // Time: O(n), Space: O(n)
  int count_nodes(Node<T> *node) const {
        if (!node) return 0;

        return count_nodes(node->left) + count_nodes(node->right) + 1;
    }

public:
  // Time: O(1), Space: O(1)
  ShawarebBinaryTree(const T &value) {
        root = new Node<T>(value);
    }

  // Time: O(n), Space: O(n)
  // Copy constructor
  ShawarebBinaryTree(const ShawarebBinaryTree<T> &otherTree) {
        if (!otherTree.root)
            root = nullptr;
        else
            copy_tree(this->root, otherTree.root);
    }

  // Time: O(n), Space: O(1)
  // Destructor - deallocates all nodes
  ~ShawarebBinaryTree() {
        destroy(root);
    }

  // Time: O(n), Space: O(1)
  // Assignment operator with self-assignment check
  ShawarebBinaryTree &operator=(const ShawarebBinaryTree<T> &otherTree) {
        if (&otherTree == this) return *this;
        destroy(root);
        copy_tree(root, otherTree.root);

        return *this;
    }

  // Time: O(1), Space: O(1)
  bool is_empty() const {
        return root == nullptr;
    }

  // Time: O(m log n), Space: O(n)
  // Inserts nodes following provided directions and values
  void insert(vector<T> values, vector<char> directions) {
        assert(values.size() == directions.size());

        Node<T> *current = root;
        for (int i = 0; i < values.size(); ++i) {
            if (directions[i] == 'L') {
                if (!current->left) {
                    current->left = new Node<T>(values[i]);
                } else {
                    assert(current->left->data == values[i]);
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new Node<T>(values[i]);
                } else {
                    assert(current->right->data == values[i]);
                }
                current = current->right;
            }
        }
    }

  // Time: O(n), Space: O(n)
  void inorder_traversal() const {
        inorder(root);
    }

  // Time: O(n), Space: O(n)
  void preorder_traversal() const {
        preorder(root);
    }

  // Time: O(n), Space: O(n)
  void postorder_traversal() const {
        postorder(root);
    }

  // Time: O(n), Space: O(n)
  int tree_height() const {
        return height(root);
    }

  // Time: O(n), Space: O(n)
  int tree_leaves_count() const {
        return count_leaves(root);
    }

  // Time: O(n), Space: O(n)
  int tree_node_count() const {
        return count_nodes(root);
    }
};

#endif
