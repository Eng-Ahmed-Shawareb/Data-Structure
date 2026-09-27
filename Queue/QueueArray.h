/**
 * ---------------------------------------------------------------------------*
 * | File Name   : QueueArray.h                                              |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Queue implementation for Data Structures (Array).         |*
 * ---------------------------------------------------------------------------*
**/

#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

#include <cassert>

template <typename T>
// Implements a queue using a fixed-size circular array.
class QueueArray {
private:
    int size {};
    int front {0};
    int rear {0};
    int added_elements {0};
    T* array {};

    // Returns the next index in the circular buffer.
    int next_index(const int& position) const {
        return (position + 1) % size;
    }
public:
    // Creates a queue with the given maximum capacity.
    QueueArray(int size) {
        if (size <= 0) {
            size = 1;
        }
        this->size = size;
        array = new T[this->size];
    }

    // Releases the memory used by the queue.
    ~QueueArray() {
        delete[] array;
        array = nullptr;
    }

    // Creates a copy of another queue.
    QueueArray(const QueueArray<T> &other) {
        size = other.size;
        front = other.front;
        rear = other.rear;
        added_elements = other.added_elements;
        array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
    }

    // Replaces this queue with a copy of another queue.
    QueueArray &operator=(const QueueArray<T> &other) {
        if (this == &other)
            return *this;
        delete[] array;

        size = other.size;
        front = other.front;
        rear = other.rear;
        added_elements = other.added_elements;
        array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
        return *this;
    }

    // Adds an element to the rear of the queue.
    void enqueue(const T& element) {
        assert(!isFull());
        array[rear] = element;
        rear = next_index(rear);
        ++added_elements;
    }

    // Removes and returns the element at the front of the queue.
    T dequeue() {
        assert(!isEmpty());
        T element = array[front];
        front = next_index(front);
        --added_elements;
        return element;
    }

    // Return the front element of the queue
    T get_front() const {
        assert(!isEmpty());
        return array[front];
    }

    // Returns true when the queue contains no elements.
    bool isEmpty() const {
        return (added_elements == 0);
    }

    // Returns true when the queue has reached its maximum capacity.
    bool isFull() const {
        return (added_elements == size);
    }
};

#endif