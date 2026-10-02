/**
 *----------------------------------------------------------------------------*
 * | File Name   : BinarySearchTree.h                                        |*
 * |                                                                         |*
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |*
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Binary Search Tree implementation for Data Structures.    |*
 * ---------------------------------------------------------------------------*
**/

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

template<typename T>
// Represents a single node in the binary search tree.
struct Node {
    T data{};
    Node<T> *right{};
    Node<T> *left{};

    // Creates a node for the specified value.
    Node(T data) : data(data) {
    }

    // Prints debug information when the node is destroyed.
    ~Node() {
        cout << "Destroy value: " << data << " at address: " << this << endl;
    }
};

template<typename T>
// Implements a binary search tree with ordered insertion and lookup.
class BinarySearchTree {
private:
    Node<T> *root;

    // Copies the tree structure and values from another binary search tree.
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

    // Deletes every node in the subtree rooted at the given node.
    void destroy(Node<T> * node) {
        if (!node) return;

        destroy(node->left);
        destroy(node->right);
        delete node;
        node = nullptr;
    }

    // Searches for a value in the subtree rooted at the given node.
    bool _search(Node<T> * node, const T& data) const {
        if (!node) {
            return false;
        }
        if (node->data == data) {
            return true;
        }
        if (node->data < data) {
            return _search(node->right, data);
        }
        return _search(node->left, data);
    }

    // Inserts a value into the subtree rooted at the given node.
    void _insert(Node<T> * node, const T& data) {
        if (data < node->data) {
            if (!node->left) {
                node->left = new Node<T>(data);
            }else {
                _insert(node->left, data);
            }
        }else {
            if (!node->right) {
                node->right = new Node<T>(data);
            }else {
                _insert(node->right, data);
            }
        }
    }

    // Finds the minimum value in the subtree rooted at the given node.
    T _minimum(Node<T> * node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node->data;
    }

    // Finds the maximum value in the subtree rooted at the given node.
    T _maximum(Node<T> * node) const {
        while (node && node->right) {
            node = node->right;
        }
        return node->data;
    }

    // Returns the left-most node in the subtree rooted at the given node.
    Node<T>* _minimum_node(Node<T>* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // Removes and returns the last ancestor from the stack of traversal nodes.
    Node<T>* _get_next(vector<Node<T>*>&ancestors) const {
        if (ancestors.empty()) {
            return nullptr;
        }
        Node<T>* current = ancestors.back();
        ancestors.pop_back();
        return current;
    }

    // Tracks the path taken while searching for a value in the tree.
    bool _find_chain(Node<T> * node, const T& data , vector<Node<T>*>&ancestors) const {
        ancestors.push_back(node);

        if (node->data == data) {
            return true;
        }

        if (node->data < data) {
            return _find_chain(node->right, data, ancestors);
        }
        return _find_chain(node->left, data, ancestors);
    }

    // Finds the successor of a value in the tree, if it exists.
    pair<bool , T> _successor(const T& data) const {
        vector<Node<T>*> ancestors;

        if (!_find_chain(root, data, ancestors)) {
            return make_pair(false, -1);
        }

        Node<T>* child = _get_next(ancestors);

        if (child->right) {
            return make_pair(true, _minimum(child->right));
        }

        Node<T>* parent = _get_next(ancestors);

        while (parent && parent->right == child) {
            child = parent;
            parent = _get_next(ancestors);
        }

        if (parent) {
            return make_pair(true, parent->data);
        }
        return make_pair(false, -1);
    }

    // Deletes the specified value from the subtree rooted at the given node.
    Node<T>* _delete(Node<T>* node , const T& data) {
        if (!node)
            return nullptr;

        if (data < node->data)
            node->left = _delete(node->left, data);
        else if (data > node->data)
            node->right = _delete(node->right, data);
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

        return node;
    }
    
public:
    // Creates a tree with the given root value.
    BinarySearchTree(const T& value) {
        root = new Node<T>(value);
    }

    // Creates a deep copy of another binary search tree.
    BinarySearchTree(const BinarySearchTree<T>& otherTree) {
        if (!otherTree.root) {
            root = nullptr;
        }else {
            copy_tree(root, otherTree.root);
        }
    }

    // Releases all nodes owned by the tree.
    ~BinarySearchTree() {
        destroy(root);
    }

    // Replaces this tree with a copy of another tree.
    BinarySearchTree &operator=(const BinarySearchTree<T> &otherTree) {
        if (&otherTree == this) return *this;
        destroy(root);
        copy_tree(root, otherTree.root);

        return *this;
    }

    // Returns true when the specified value exists in the tree.
    bool search(const T& data) const {
        return _search(root, data);
    }

    // Inserts a value into the binary search tree.
    void insert(const T& data) {
        if (!root) {
            root = new Node<T>(data);
            return;
        }
        _insert(root, data);
    }

    // Returns the smallest value in the tree.
    T minimum() const {
        assert(!is_empty());
        return _minimum(root);
    }

    // Returns the largest value in the tree.
    T maximum() const {
        assert(!is_empty());
        return _maximum(root);
    }

    // Removes the specified value from the tree.
    void erase(const T& data) {
        root = _delete(root, data);
    }

    // Returns true when the tree contains no nodes.
    bool is_empty() const {
        return (root == nullptr);
    }

};

#endif