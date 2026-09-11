/**
 * ---------------------------------------------------------------------------*
 * | File Name   : DoubleLinkedList.h                                        |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Double linked list implementation for Data Structures.    |*
 * ---------------------------------------------------------------------------*
**/

#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

#include <iostream>
using namespace std;

template <class T>
// Represents a list node with links to the next and previous nodes.
class Node {
public:
  T data;
  Node<T> *next = nullptr;
  Node<T> *previous = nullptr;

  // Creates a node containing the given value.
  Node(const T &d) : data(d) {}
  // Displays information about the node being destroyed.
  ~Node() {
    cout << "Destroy value: " << data << " at address: " << this << endl;
  }
};

template <class T>
// Stores elements in a sequence of nodes linked in both directions.
class DoubleLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int length;

  // Connects two neighboring nodes in the list.
  void link(Node<T> *first, Node<T> *second) {
    if (first)
      first->next = second;
    if (second)
      second->previous = first;
  }

  // Removes a node and reconnects its neighboring nodes.
  Node<T> *delete_and_link(Node<T> *node) {
    Node<T> *ret = node->previous;
    link(node->previous, node->next);
    delete_node(node);
    return ret;
  }

  // Deletes a node and updates the list length.
  void delete_node(Node<T> *node) {
    delete node;
    --length;
  }

  // Deletes all nodes and resets the list to an empty state.
  void clear() {
    while (head) {
      Node<T> *next = head->next;
      delete_node(head);
      head = next;
    }
    tail = nullptr;
  }

public:
  // Creates an empty doubly linked list.
  DoubleLinkedList() : head(nullptr), tail(nullptr), length(0) {}

  // Creates a deep copy of another doubly linked list.
  DoubleLinkedList(const DoubleLinkedList<T> &otherList)
      : head(nullptr), tail(nullptr), length(0) {
    for (Node<T> *current = otherList.head; current; current = current->next) {
      insert_end(current->data);
    }
  }

  // Replaces this list with a deep copy of another doubly linked list.
  DoubleLinkedList &
  operator=(const DoubleLinkedList<T> &otherList) {
    if (&otherList == this)
      return *this;
    clear();
    for (Node<T> *current = otherList.head; current; current = current->next) {
      insert_end(current->data);
    }
    return *this;
  }

  // Adds a new value to the end of the list.
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

  // Adds a new value to the beginning of the list.
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

  // Inserts a value into its correct position in a sorted list.
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

    for (Node<T> *current = head; current; current = current->next) {
      if (value >= current->data && value <= current->next->data) {
        Node<T> *new_node = new Node<T>(value);
        Node<T> *next = current->next;
        link(current, new_node);
        link(new_node, next);
        ++length;
        break;
      }
    }
  }

  // Removes the first node from the list.
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

  // Removes the last node from the list.
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

  // Removes the first node containing the specified value.
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

  // Prints all values from the beginning to the end of the list.
  void print() {
    for (Node<T> *current = head; current; current = current->next) {
      cout << current->data << " ";
    }
    cout << endl;
  }

  // Returns true when the list contains no nodes.
  bool is_empty() const {
    return head == nullptr;
  }

  // Returns the number of nodes currently stored in the list.
  int get_size() const {
    return length;
  }

  // Releases all nodes owned by the list.
  ~DoubleLinkedList() { clear(); }
};
#endif