/**
* ---------------------------------------------------------------------------*
 * | File Name   : AVLTree.h                                                 |*
 * |                                                                         |*
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |*
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : AVL Tree implementation for Data Structures.              |*
 * ---------------------------------------------------------------------------*
**/

#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

template<typename T>
// Represents a single AVL tree node, including its height and child links.
struct Node {
 T data{};
 int height{};
 Node<T> *right{};
 Node<T> *left{};

 // Creates a node containing the given value.
 Node(T data) : data(data) {
 }

 // Displays information when the node is destroyed.
 ~Node() {
  cout << "Destroy value: " << data << " at address: " << this << endl;
 }

 // Returns the height of the given child node, or -1 for a null child.
 int child_height(Node<T> *node) const {
  if (!node) return -1;
  return node->height;
 }

 // Recomputes the node height based on its left and right subtree heights.
 void update_height() {
  height = 1 + max(child_height(left), child_height(right));
 }

 // Returns the difference between the left and right subtree heights.
 int balance_factor() const {
  return child_height(left) - child_height(right);
 }
};

template<typename T>
// Implements an AVL tree, a self-balancing binary search tree.
class AVLTree {
private:
 Node<T> *root{};

 // Rotates the subtree to the right, restoring the AVL balance.
 Node<T>* _right_rotation(Node<T> *node) {
  Node<T>* left_node = node->left;
  node->left = left_node->right;
  left_node->right = node;

  node->update_height();
  left_node->update_height();

  return left_node;
 }

 // Rotates the subtree to the left, restoring the AVL balance.
 Node<T>* _left_rotation(Node<T> *node) {
  Node<T>* right_node = node->right;
  node->right = right_node->left;
  right_node->left = node;

  node->update_height();
  right_node->update_height();

  return right_node;
 }

 // Balances a node that violates the AVL height property.
 Node<T>* _balance(Node<T> *node) {
  if (node->balance_factor() == 2) {
   if (node->left->balance_factor() == -1)
    node->left = _left_rotation(node->left);
   node = _right_rotation(node);
  }else if (node->balance_factor() == -2) {
   if (node->right->balance_factor() == 1)
    node->right = _right_rotation(node->right);
   node = _left_rotation(node);
  }
  return node;
 }

 // Inserts a value into the subtree rooted at the given node and rebalances it.
 Node<T>* _insert(Node<T> *node, const T& data) {
  if (data < node->data) {
   if (!node->left)
    node->left = new Node<T>(data);
   else
    node->left = _insert(node->left, data);
  }else {
   if (!node->right)
    node->right = new Node<T>(data);
   else
    node->right = _insert(node->right, data);
  }
  node->update_height();
  return _balance(node);
 }

 // Returns the left-most node in the subtree rooted at the given node.
 Node<T>* _minimum_node(Node<T>* node) const {
  while (node && node->left) {
   node = node->left;
  }
  return node;
 }

 // Deletes the specified value from the subtree rooted at the given node.
 Node<T>* _delete(Node<T> *node , const T& data) {
  if (!node) {
   return nullptr;
  }
  if (data < node->data) {
   node->left = _delete(node->left, data);
  }
  else if (data > node->data) {
   node->right = _delete(node->right, data);
  }
  else {
   Node<T>* temp = node;
   if (!node->right && !node->left)
    node = nullptr;
   else if (!node->left) {
    node = node->right;
   }
   else if (!node->right) {
    node = node->left;
   }
   else {
    Node<T>* mn = _minimum_node(node->right);
    node->data = mn->data;
    node->right = _delete(node->right, mn->data);
    temp = nullptr;
   }
   if (temp) delete temp;
  }
  if (node) {
   node->update_height();
   node = _balance(node);
  }
  return node;
 }

 // Searches for the given value in the subtree rooted at the given node.
 bool _find(Node<T> *node, const T& data) const {
  if (!node) {
   return false;
  }
  if (data < node->data) {
   return _find(node->left, data);
  }
  if (data > node->data) {
   return _find(node->right, data);
  }
  return true;
 }

 // Copies the entire AVL subtree structure from another tree.
 void _copy_tree(Node<T> *otherTree, Node<T>* &node) {
  if (!otherTree) {
   node = nullptr;
   return;
  }else {
   node = new Node<T>(otherTree->data);
   _copy_tree(otherTree->left, node->left);
   _copy_tree(otherTree->right, node->right);
  }
 }

 // Deletes all nodes in the subtree rooted at the given node.
 void _clear_tree(Node<T>* &node) {
  if (!node) return;
  _clear_tree(node->left);
  _clear_tree(node->right);
  delete node;
  node = nullptr;
 }
public:
 // Creates an empty AVL tree.
 AVLTree() {}

 // Creates an AVL tree with the given root value.
 AVLTree(const T& data) {
  root = new Node<T>(data);
 }

 // Creates a deep copy of another AVL tree.
 AVLTree(const AVLTree &tree) {
  _copy_tree(tree.root, root);
 }

 // Replaces the current tree with a copy of another tree.
 AVLTree& operator=(const AVLTree& tree) {
  if (this == &tree) {
   return *this;
  }
  _clear_tree(root);
  _copy_tree(tree.root, root);
  return *this;
 }

 // Releases all nodes owned by the tree.
 ~AVLTree() {
  _clear_tree(root);
 }

 // Returns true when the tree contains no nodes.
 bool is_empty() const {
  return !root;
 }

 // Inserts a value into the AVL tree and rebalances it.
 void insert(const T& data) {
  if (is_empty()) {
   root = new Node<T>(data);
   return;
  }
  root = _insert(root, data);
 }

 // Removes the specified value from the AVL tree.
 void erase(const T& data) {
  assert(!is_empty());
  root = _delete(root, data);
 }

 // Returns true when the specified value exists in the tree.
 bool find(const T& data) const {
  return _find(root, data);
 }
};

#endif // AVL_TREE