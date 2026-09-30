/**
 * ---------------------------------------------------------------------------*
 * | File Name   : SingleLinkedList.h                                        |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Single linked list implementation for Data Structures.    |*
 * ---------------------------------------------------------------------------*
**/

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

template <class T>
// Represents one element in the singly linked list.
class Node {
public:
  T data;
  Node<T> *next;
  // Creates a node containing the given value.
  Node(const T &d) : data(d) { next = nullptr; }
  // Displays information about the node being destroyed.
  ~Node() {
    cout << "Destroy value: " << data << " at address: " << this << endl;
  }
};

template <class T>
// Stores elements in a sequence of nodes connected in one direction.
class SingleLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int length;

  // Deletes a node and updates the number of stored elements.
  void delete_node(Node<T> *node) {
    delete node;
    --length;
  }

  // Deletes every node and resets the list to an empty state.
  void clear() {
    while (head) {
      Node<T> *next = head->next;
      delete_node(head);
      head = next;
    }
    tail = nullptr;
  }

public:
  // Creates an empty linked list.
  SingleLinkedList() : head(nullptr), tail(nullptr), length(0) {}

  // Creates a deep copy of another linked list.
  SingleLinkedList(const SingleLinkedList<T> &otherList)
      : head(nullptr), tail(nullptr), length(0) {
    for (Node<T> *current = otherList.head; current; current = current->next) {
      insert_end(current->data);
    }
  }

  // Replaces this list with a deep copy of another linked list.
  SingleLinkedList<T> &
  operator=(const SingleLinkedList<T> &otherList) {
    if (&otherList == this)
      return *this;

    clear();

    for (Node<T> *current = otherList.head; current; current = current->next) {
      insert_end(current->data);
    }

    return *this;
  }

  // Releases all nodes owned by the list.
  ~SingleLinkedList() { clear(); }

  // Adds a new value to the end of the list.
  void insert_end(const T &value) {
    Node<T> *new_node = new Node<T>(value);

    if (!head) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
    ++length;
  }

  // Adds a new value to the beginning of the list.
  void insert_front(const T &value) {
    Node<T> *new_node = new Node<T>(value);
    new_node->next = head;
    head = new_node;
    if (length == 0)
      tail = head;
    ++length;
  }

  //Return the first element in the linked list.
  T get_front() const {
    assert(!is_empty());
    return head->data;
  }

  //Return the last element in the linked list.
  T get_back() const {
    assert(!is_empty());
    return tail->data;
  }

  // Inserts a value into its correct position in a sorted list.
  void insert_sorted(const T &value) {
    if (length == 0) {
      insert_end(value);
      return;
    }
    if (length == 1) {
      if (head->data > value)
        insert_front(value);
      else
        insert_end(value);
      return;
    }
    if (tail->data <= value) {
      insert_end(value);
      return;
    }
    if (head->data >= value) {
      insert_front(value);
      return;
    }
    for (Node<T> *current = head->next, *previous = head; current;
         previous = current, current = current->next) {
      if (value >= previous->data && value <= current->data) {
        Node<T> *new_node = new Node<T>(value);
        new_node->next = current;
        previous->next = new_node;
        length++;
        break;
      }
    }
  }

  // Returns the node at the specified one-based position.
  Node<T> *get_nth(const int &order) const {
    assert(order >= 1 && order <= length);
    int counter = 0;
    for (Node<T> *current = head; current; current = current->next) {
      if (++counter == order) {
        return current;
      }
    }
    return nullptr;
  }

  // Returns the node at the specified one-based position from the end.
  Node<T> *get_nth_back(const int &order) const {
    return get_nth(length - order + 1);
  }

  // Returns the one-based position of the first matching value.
  // Returns -1 when the value is not found.
  int search(const T &value) const {
    int index = 1;
    for (Node<T> *current = head; current; current = current->next, index++) {
      if (current->data == value) {
        return index;
      }
    }
    return -1;
  }

  // Removes the first node from the list.
  void delete_front() {
    if (head) {
      Node<T> *current = head;
      head = head->next;
      delete_node(current);
      if (!head)
        tail = nullptr;
    }
  }

  // Removes the last node from the list.
  void delete_end() {
    if (length <= 1) {
      delete_front();
      return;
    }

    Node<T> *previous = get_nth(length - 1);

    delete_node(tail);

    tail = previous;
    tail->next = nullptr;
  }

  // Removes the node at the specified one-based position.
  void delete_nth(const int &n) {
    assert(n >= 1 && n <= length);

    if (n == 1) {
      delete_front();
      return;
    }

    Node<T> *previous = get_nth(n - 1);
    Node<T> *nth = previous->next;
    bool is_tail = nth == tail;
    previous->next = nth->next;
    delete_node(nth);
    if (is_tail)
      tail = previous;
  }

  void delete_with_key(const T &key) {
    int counter = 1;
    for (Node<T> *current = head; current; current = current->next, ++counter) {
      if (current->data == key) {
        delete_nth(counter);
        return;
      }
    }
    cout << "value not found!" << endl;
  }

  // Reverses the order of all nodes in the list.
  void reverse() {
    if (length <= 1)
      return;

    tail = head;
    Node<T> *previous = head;
    head = head->next;
    while (head) {
      Node<T> *next = head->next;
      head->next = previous;

      previous = head;
      head = next;
    }
    head = previous;
    tail->next = nullptr;
  }

  // Returns true when the list contains no nodes.
  bool is_empty() const {
    return head == nullptr;
  }

  // Returns the number of nodes currently stored in the list.
  int get_size() const {
    return length;
  }
};

#endif