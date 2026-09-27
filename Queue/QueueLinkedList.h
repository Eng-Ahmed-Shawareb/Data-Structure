/**
 * ---------------------------------------------------------------------------*
 * | File Name   : QueueLinkedList.h                                         |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Queue implementation for Data Structures (LinkedList).    |*
 * ---------------------------------------------------------------------------*
**/

#ifndef QUEUE_LINKED_LIST_H
#define QUEUE_LINKED_LIST_H

#include "../Linked List/SingleLinkedList.h"
#include <cassert>

template <typename T>
// Implements a queue by wrapping a singly linked list.
class QueueLinkedList {
private:
    SingleLinkedList<T> list;
public:
    // Creates an empty queue.
    QueueLinkedList() {

    }

    // Releases the underlying linked list memory.
    ~QueueLinkedList() {

    }

    // Creates a copy of another queue.
    QueueLinkedList(const QueueLinkedList<T> &other) : list(other.list) {}

    // Replaces this queue with a copy of another queue.
    QueueLinkedList &operator=(const QueueLinkedList<T> &other) {
        list = other.list;
        return *this;
    }

    // Adds an item to the back of the queue.
    void enqueue(const T& item) {
        list.insert_end(item);
    }

    // Removes and returns the item at the front of the queue.
    T dequeue() {
        assert(!list.is_empty());
        T item = list.get_front();
        list.delete_front();
        return item;
    }

    // Returns the front item without removing it.
    T get_front() const {
        assert(!list.is_empty());
        return list.get_front();
    }

    // Returns the number of items currently stored in the queue.
    int get_size() const {
        return list.get_size();
    }

    // Returns true when the queue contains no items.
    bool isEmpty() const {
        return list.is_empty();
    }
};

#endif