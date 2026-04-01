/**
 * ---------------------------------------------------------------------------*
 * | File Name   : ShawarebQueueLinkedListBased.h                            |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Stack implementation for Data Structures.                 |*
 * ---------------------------------------------------------------------------*
**/

#ifndef SHAWAREB_QUEUE_LINKED_LIST_BASED_H
#define SHAWAREB_QUEUE_LINKED_LIST_BASED_H

#include "ShawarebSingleLinkedList.h"

template <typename T>
// Queue implemented using single linked list (FIFO - First In First Out)
class ShawarebQueueLinkedListBased {
private:
  ShawarebSingleLinkedList<T> list;

public:
  // Time: O(1), Space: O(1)
  ShawarebQueueLinkedListBased() {}

  // Time: O(n), Space: O(n)
  // Copy constructor
  ShawarebQueueLinkedListBased(const ShawarebQueueLinkedListBased &other)
      : list(other.list) {}

  // Time: O(n), Space: O(1)
  // Assignment operator with self-assignment check
  ShawarebQueueLinkedListBased &
  operator=(const ShawarebQueueLinkedListBased &other) {
    if (this != &other)
      list = other.list;
    return *this;
  }

  // Time: O(1), Space: O(1)
  // Adds element to back of queue
  void enqueue(const T &value) { list.insert_end(value); }

  // Time: O(1), Space: O(1)
  // Removes and returns element from front of queue
  T dequeue() {
    assert(!isEmpty());
    T value = list.get_nth(1)->data;
    list.delete_front();
    return value;
  }

  // Time: O(1), Space: O(1)
  bool isEmpty() { return list.isEmpty(); }
};

#endif