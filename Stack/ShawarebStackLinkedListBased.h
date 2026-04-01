/**
 * ---------------------------------------------------------------------------*
 * | File Name   : ShawarebSingleLinkedList.h                                |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Stack implementation for Data Structures.                 |*
 * ---------------------------------------------------------------------------*
**/

#ifndef SHAWAREB_STACK_LINKED_LIST_BASED_H
#define SHAWAREB_STACK_LINKED_LIST_BASED_H

#include <cassert>
#include <iostream>
using namespace std;

template <typename T>
// Node for stack linked list
class Node {
public:
  T data;
  Node<T> *next;
  Node(const T &d) : data(d) { next = nullptr; }
  ~Node() {
    cout << "Destroy value: " << data << "at adress: " << this << endl;
  }
};

template <typename T>
// Stack implemented using linked list (LIFO - Last In First Out)
class ShawarebStackLinkedListBased {
private:
  Node<T> *head;
  int length;

  // Time: O(n), Space: O(n)
  // Deep copies nodes from another stack
  void copy_from(const ShawarebStackLinkedListBased &other) {
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

  // Time: O(n), Space: O(1)
  // Deallocates all nodes in the stack
  void clear() {
    while (head) {
      Node<T> *temp = head;
      head = head->next;
      delete temp;
    }
    length = 0;
  }

public:
  // Time: O(1), Space: O(1)
  ShawarebStackLinkedListBased() : head(nullptr), length(0) {}

  // Time: O(n), Space: O(n)
  // Copy constructor
  ShawarebStackLinkedListBased(const ShawarebStackLinkedListBased &other) {
    copy_from(other);
  }

  // Time: O(n), Space: O(1)
  // Assignment operator with self-assignment check
  ShawarebStackLinkedListBased &
  operator=(const ShawarebStackLinkedListBased &other) {
    if (this != &other) {
      clear();
      copy_from(other);
    }
    return *this;
  }

  // Time: O(n), Space: O(1)
  // Destructor - deallocates all nodes
  ~ShawarebStackLinkedListBased() { clear(); }

  // Time: O(1), Space: O(1)
  void push(const T &value) {
    Node<T> *new_node = new Node<T>(value);
    new_node->next = head;
    head = new_node;
    ++length;
  }

  // Time: O(1), Space: O(1)
  bool isEmpty() { return !head; }

  // Time: O(1), Space: O(1)
  // Removes and returns top element from stack
  T pop() {
    assert(!isEmpty());

    T data = head->data;
    Node<T> *next = head->next;
    delete head;
    head = next;
    --length;
    return data;
  }
};

#endif