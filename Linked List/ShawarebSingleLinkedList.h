/**
 * ---------------------------------------------------------------------------*
 * | File Name   : ShawarebSingleLinkedList.h                                |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Single linked list implementation for Data Structures.    |*
 * ---------------------------------------------------------------------------*
**/

#ifndef SHAWAREB_SINGLE_LINKED_LIST_H
#define SHAWAREB_SINGLE_LINKED_LIST_H

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

template <class T>
// Node for singly linked list
class Node {
public:
  T data;
  Node<T> *next;
  Node(const T &d) : data(d) { next = nullptr; }
  ~Node() {
    cout << "Destroy value: " << data << " at adress: " << this << endl;
  }
};

template <class T>
// Singly linked list implementation
class ShawarebSingleLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int length;

  // Time: O(1), Space: O(1)
  void delete_node(Node<T> *node) {
    delete node;
    --length;
  }

  // Time: O(1), Space: O(1)
  void delete_next(Node<T> *previous) {
    if (!previous->next)
      return;

    Node<T> *to_delete = previous->next; // Store the pointer first

    if (to_delete == tail)
      tail = previous;

    previous->next = to_delete->next;
    delete_node(to_delete); // This frees memory AND decrements length
  }

public:
  ShawarebSingleLinkedList() : head(nullptr), tail(nullptr), length(0) {}

  // Time: O(m), Space: O(m)  m->length of otherList
  // Copy constructor
  ShawarebSingleLinkedList(const ShawarebSingleLinkedList<T> &otherList)
      : head(nullptr), tail(nullptr), length(0) {
    for (Node<T> *current = otherList.head; current; current = current->next) {
      insert_end(current->data);
    }
  }

  // Time: O(n+m), Space: O(m)  m->length of otherList
  // Assignment operator
  ShawarebSingleLinkedList<T> &
  operator=(const ShawarebSingleLinkedList<T> &otherList) {
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
      tail->next = new_node;
      tail = new_node;
    }
    ++length;
  }

  // Time: O(1), Space: O(1)
  void insert_front(const T &value) {
    Node<T> *new_node = new Node<T>(value);
    new_node->next = head;
    head = new_node;
    if (length == 0)
      tail = head;
    ++length;
  }

  // Time: O(n), Space: O(1)
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
    // Find correct position for new value
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

  // Time: O(n), Space: O(1)
  // Returns the node at position 'order' (1-based indexing)
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

  // Time: O(n), Space: O(1)
  // Returns the node at position 'order' from the end (1-based from back)
  Node<T> *get_nth_back(const int &order) const {
    return get_nth(length - order + 1);
  }

  // Time: O(n), Space: O(1)
  // Returns 0-based index of first occurrence, or -1 if not found
  int search(const T &value) const {
    int index = 0;
    for (Node<T> *current = head; current; current = current->next, index++) {
      if (current->data == value) {
        return index;
      }
    }
    return -1;
  }

  // Time: O(1), Space: O(1)
  void delete_front() {
    if (head) {
      Node<T> *current = head;
      head = head->next;
      delete_node(current);
      if (!head)
        tail = nullptr;
    }
  }

  // Time: O(n), Space: O(1)
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

  // Time: O(n), Space: O(1)
  // Deletes element at position n (1-based indexing)
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

  // Time: O(n), Space: O(1)
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

  // Time: O(n), Space: O(1)
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

  // Time: O(n²), Space: O(1)
  // Removes duplicate values keeping first occurrence
  void remove_duplicates() {
    if (length <= 1)
      return;

    for (Node<T> *current = head; current; current = current->next) {
      for (Node<T> *forward = current->next, *previous = current; forward;) {
        if (current->data == forward->data) {
          previous->next = forward->next;
          if (tail == forward)
            tail = previous;
          delete_node(forward);
          forward = previous->next;
        } else {
          previous = forward;
          forward = forward->next;
        }
      }
    }
  }

  // Time: O(n), Space: O(1)
  // Removes all duplicate values (elements that appear more than once).
  // Requires: list must be sorted
  void remove_all_duplicates() {
    if (length <= 1)
      return;

    T last_value;
    bool is_declared = false;

    for (Node<T> *current = head, *previous = nullptr; current;) {
      bool flag = false;
      // Remove all occurrences of duplicate values
      while ((current->next && current->data == current->next->data) ||
             (is_declared && current->data == last_value)) {
        flag = true;
        is_declared = true;
        last_value = current->data;
        if (previous == nullptr) {
          Node<T> *next = current->next;
          delete_front();
          current = next;
        } else {
          previous->next = current->next;
          delete_node(current);
          current = previous->next;
        }
        if (!current) {
          tail = previous;
          break;
        }
      }
      if (!flag) {
        previous = current;
        current = current->next;
      }
    }
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
  ~ShawarebSingleLinkedList() { clear(); }
};

#endif