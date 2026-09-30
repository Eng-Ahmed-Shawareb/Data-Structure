/**
* ---------------------------------------------------------------------------*
 * | File Name   : BinaryTree.h                                              |*
 * |                                                                         |*
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |*
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Binary Tree implementation for Data Structures.           |*
 * ---------------------------------------------------------------------------*
**/

#ifndef BINARY_TREE
#define BINARY_TREE

#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template<typename T>
// Stores a value and the left/right child pointers of a binary-tree node.
struct Node {
    T data{};
    Node<T> *right{};
    Node<T> *left{};

    // Creates a node with the provided value.
    Node(T data) : data(data) {
    }

    // Displays information when the node is destroyed.
    ~Node() {
        cout << "Destroy value: " << data << " at address: " << this << endl;
    }
};

template<typename T>
// Represents a binary tree and provides traversal and tree-analysis operations.
class BinaryTree {
private:
  Node<T> *root;

  // Copies the structure and values from another tree into this tree.
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

  // Deletes all nodes in the subtree rooted at the given node.
  void destroy(Node<T> * &node) {
        if (!node) return;

        destroy(node->left);
        destroy(node->right);
        delete node;
        node = nullptr;
    }

  // Prints the subtree in left-root-right order.
  void inorder(Node<T> *node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

  // Prints the subtree in root-left-right order.
  void preorder(Node<T> *node) const {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

  // Prints the subtree in left-right-root order.
  void postorder(Node<T> *node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

  // Returns the height of the subtree rooted at the given node.
  int height(Node<T> *node) const {
        if (!node) return 0;

        return max(height(node->left) + 1, height(node->right) + 1);
    }

  // Counts the leaves in the subtree rooted at the given node.
  int count_leaves(Node<T> *node) const {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;

        return count_leaves(node->left) + count_leaves(node->right);
    }

  // Counts all nodes in the subtree rooted at the given node.
  int count_nodes(Node<T> *node) const {
        if (!node) return 0;

        return count_nodes(node->left) + count_nodes(node->right) + 1;
    }

public:
  // Creates a binary tree with the given root value.
  BinaryTree(const T &value) {
        root = new Node<T>(value);
    }

  // Creates a deep copy of another binary tree.
  BinaryTree(const BinaryTree<T> &otherTree) {
        if (!otherTree.root)
            root = nullptr;
        else
            copy_tree(this->root, otherTree.root);
    }

  // Deletes all nodes in the tree.
  ~BinaryTree() {
        destroy(root);
    }

  // Replaces the current tree with a copy of another tree.
  BinaryTree &operator=(const BinaryTree<T> &otherTree) {
        if (&otherTree == this) return *this;
        destroy(root);
        copy_tree(root, otherTree.root);

        return *this;
    }

  // Returns true when the tree contains no nodes.
  bool is_empty() const {
        return root == nullptr;
    }

  // Inserts a sequence of values using a path of left/right directions.
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

  // Prints the tree using an in-order traversal.
  void inorder_traversal() const {
        inorder(root);
    }

  // Prints the tree using a pre-order traversal.
  void preorder_traversal() const {
        preorder(root);
    }

  // Prints the tree using a post-order traversal.
  void postorder_traversal() const {
        postorder(root);
    }

  // Returns the height of the tree.
  int tree_height() const {
        return height(root);
    }

  // Returns the number of leaves in the tree.
  int tree_leaves_count() const {
        return count_leaves(root);
    }

  // Returns the total number of nodes in the tree.
  int tree_node_count() const {
        return count_nodes(root);
    }
};

#endif
