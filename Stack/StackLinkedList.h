/**
 * ---------------------------------------------------------------------------*
 * | File Name   : StackLinkedList.h                                         |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Stack implementation for Data Structures (linked list).   |*
 * ---------------------------------------------------------------------------*
**/

#ifndef STACK_LINKED_LIST_H
#define STACK_LINKED_LIST_H

#include <cassert>
#include <iostream>
using namespace std;

template <typename T>
// Represents a single node in the linked-list stack.
class Node {
public:
  T data;
  Node<T> *next;
  // Creates a node containing the provided value.
  Node(const T &d) : data(d) { next = nullptr; }
  // Displays information when the node is destroyed.
  ~Node() {
    cout << "Destroy value: " << data << "at address: " << this << endl;
  }
};

template <typename T>
// Implements a stack using a singly linked list.
class StackLinkedList {
private:
  Node<T> *head;
  int length;

  // Copies all nodes from another stack into this one.
  void copy(const StackLinkedList &other) {
    if (other.head == nullptr) {
      head = nullptr;
      length = 0;
      return;
    }

    head = new Node<T>(other.head->data);
    Node<T> *current = head;
    Node<T> *otherCurrent = other.head->next;

    while (otherCurrent) {
      current->next = new Node<T>(otherCurrent->data);
      current = current->next;
      otherCurrent = otherCurrent->next;
    }

    length = other.length;
  }

  // Removes all nodes and resets the stack to an empty state.
  void clear() {
    while (head) {
      Node<T> *temp = head;
      head = head->next;
      delete temp;
    }
    length = 0;
  }

public:
  // Creates an empty stack.
  StackLinkedList() : head(nullptr), length(0) {}

  // Creates a copy of another stack.
  StackLinkedList(const StackLinkedList &other) {
    copy(other);
  }

  // Replaces this stack with a copy of another stack.
  StackLinkedList &
  operator=(const StackLinkedList &other) {
    if (this != &other) {
      clear();
      copy(other);
    }
    return *this;
  }

  // Releases all memory used by the stack.
  ~StackLinkedList() { clear(); }

  // Adds a value to the top of the stack.
  void push(const T &value) {
    Node<T> *new_node = new Node<T>(value);
    new_node->next = head;
    head = new_node;
    ++length;
  }

  // Returns true when the stack contains no elements.
  bool is_empty() const { return (!head); }

  // Removes and returns the value at the top of the stack.
  T pop() {
    assert(!is_empty());

    T data = head->data;
    Node<T> *next = head->next;
    delete head;
    head = next;
    --length;
    return data;
  }
};

#endif