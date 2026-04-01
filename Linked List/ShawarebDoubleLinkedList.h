/**
 * ---------------------------------------------------------------------------*
 * | File Name   : ShawarebSingleLinkedList.h                                |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Double linked list implementation for Data Structures.    |*
 * ---------------------------------------------------------------------------*
**/

#ifndef SHAWAREB_DOUBLE_LINKED_LIST
#define SHAWAREB_DOUBLE_LINKED_LIST

#include <cassert>
#include <iostream>
using namespace std;

template <class T>
// Node for doubly linked list with forward and backward pointers
class Node {
public:
  T data;
  Node<T> *next = nullptr;
  Node<T> *previous = nullptr;

  Node(const T &d) : data(d) {}
  ~Node() {
    cout << "Destroy value: " << data << " at adress: " << this << endl;
  }
};

template <class T>
// Doubly linked list implementation with bidirectional traversal
class ShawarebDoubleLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int length;

  // Time: O(1), Space: O(1)
  // Links two nodes by setting next and previous pointers
  void link(Node<T> *first, Node<T> *second) {
    if (first)
      first->next = second;
    if (second)
      second->previous = first;
  }

  // Time: O(1), Space: O(1)
  // Removes node from list by linking its neighbors
  Node<T> *delete_and_link(Node<T> *node) {
    Node<T> *ret = node->previous;
    link(node->previous, node->next);
    delete_node(node);
    return ret;
  }

  // Time: O(1), Space: O(1)
  void delete_node(Node<T> *node) {
    delete node;
    --length;
  }

public:
  // Time: O(1), Space: O(1)
  ShawarebDoubleLinkedList() : head(nullptr), tail(nullptr), length(0) {}

  // Time: O(m), Space: O(m) // m->otherList length
  // Copy constructor
  ShawarebDoubleLinkedList(const ShawarebDoubleLinkedList<T> &otherList)
      : head(nullptr), tail(nullptr), length(0) {
    for (Node<T> *current = otherList.head; current; current = current->next) {
      insert_end(current->data);
    }
  }

  // Time: O(n+m), Space: O(m) // m->otherList length
  // Assignment operator with self-assignment check
  ShawarebDoubleLinkedList &
  operator=(const ShawarebDoubleLinkedList<T> &otherList) {
    if (&otherList == this)
      return *this;
    clear();
    for (Node<T> *current = otherList.head; current; current = current->next) {
      insert_end(current->data);
    }
    return *this;
  }

  // Time: O(1), Space: O(1)
  void insert_end(const T &value) {
    Node<T> *new_node = new Node<T>(value);

    if (!head) {
      head = tail = new_node;
    } else {
      link(tail, new_node);
      tail = new_node;
    }
    ++length;
  }

  // Time: O(1), Space: O(1)
  void insert_front(const T &value) {
    Node<T> *new_node = new Node<T>(value);

    if (!head) {
      head = tail = new_node;
    } else {
      link(new_node, head);
      head = new_node;
    }
    ++length;
  }

  // Time: O(n), Space: O(1)
  // Inserts value at correct sorted position. Requires: list must be sorted
  void insert_sorted(const T &value) {
    if (!length) {
      insert_end(value);
      return;
    }
    if (value >= tail->data) {
      insert_end(value);
      return;
    }
    if (value <= head->data) {
      insert_front(value);
      return;
    }

    // Find correct position for new value
    for (Node<T> *current = head; current; current = current->next) {
      if (value >= current->data && value <= current->next->data) {
        Node<T> *new_node = new Node<T>(value);
        Node<T> *next = current->next;
        link(current, new_node);
        link(new_node, next);
        break;
      }
    }
    ++length;
  }

  // Time: O(1), Space: O(1)
  void delete_front() {
    if (!head)
      return;

    if (length == 1) {
      delete_node(head);
      head = tail = nullptr;
    } else {
      head = head->next;
      delete_node(head->previous);
      head->previous = nullptr;
    }
  }

  // Time: O(1), Space: O(1)
  void delete_end() {
    if (!head)
      return;

    if (length == 1) {
      delete_node(head);
      head = tail = nullptr;
    } else {
      tail = tail->previous;
      delete_node(tail->next);
      tail->next = nullptr;
    }
  }

  // Time: O(n), Space: O(1)
  void delete_with_key(const T &value) {
    if (!head)
      return;
    if (head->data == value) {
      delete_front();
      return;
    }

    for (Node<T> *current = head; current; current = current->next) {
      if (current->data == value) {
        current = delete_and_link(current);
        if (!current->next)
          tail = current;
        break;
      }
    }
  }

  // Time: O(n), Space: O(1)
  void print() {
    for (Node<T> *current = head; current; current = current->next) {
      cout << current->data << " ";
    }
    cout << endl;
  }

  // Time: O(n), Space: O(1)
  void clear() {
    while (head) {
      Node<T> *next = head->next;
      delete_node(head);
      head = next;
    }
    tail = nullptr;
  }

  // Time: O(n), Space: O(1)
  // Destructor - deallocates all nodes
  ~ShawarebDoubleLinkedList() { clear(); }
};
#endif