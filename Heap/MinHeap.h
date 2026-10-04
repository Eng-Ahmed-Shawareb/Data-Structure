/**
 * ---------------------------------------------------------------------------*
 * | File Name   : MinHeap.h                                                 |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Min heap implementation for Data Structures.              |*
 * ---------------------------------------------------------------------------*
**/

#ifndef MIN_HEAP
#define MIN_HEAP

#include <cassert>
#include <concepts>
#include <bits/std_thread.h>

using namespace std;

template <typename T>
// Implements a min-heap that keeps the smallest value at the root.
class MaxHeap {
private:
    int size {};
    int capacity {};
    T* array {};

    // Doubles the internal storage and copies the existing elements.
    void expand_capacity() {
        capacity *= 2;
        T *array2 = new T[capacity];
        for (int i = 0; i < size; ++i) array2[i] = array[i];
        delete[] array;
        array = array2;
    }

    // Returns the left child index, or -1 when no child exists.
    int _left_child_index(const int& index) const {
        int p = (index * 2) + 1;
        if (p < size) return p;
        return -1;
    }

    // Returns the right child index, or -1 when no child exists.
    int _right_child_index(const int& index) const {
        int p = (index * 2) + 2;
        if (p < size) return p;
        return -1;
    }

    // Returns the parent index for the given node.
    int _parent_index(const int& index) const {
        return (index == 0) ? -1 : ((index - 1) / 2);
    }

    // Moves a newly inserted value upward until the heap order is restored.
    void _heapify_up(const int& index) {
        int parent_index = _parent_index(index);
        if (index == 0 || array[parent_index] < array[index]) {
            return;
        }

        swap(array[index], array[parent_index]);
        _heapify_up(parent_index);
    }

    // Moves a value downward until the heap order is restored.
    void _heapify_down(const int& index) {
        int child_index = _left_child_index(index);
        int right_child = _right_child_index(index);

        if (child_index == -1)
            return;

        if (right_child != -1 && array[right_child] < array[child_index])
            swap(right_child, child_index);

        if (array[index] > array[child_index]) {
            swap(array[index], array[child_index]);
            _heapify_down(child_index);
        }
    }
public:
    // Creates an empty heap with an initial internal capacity.
    MaxHeap() {
        capacity = 10;
        array = new T[capacity];
    }

    // Creates a copy of another min-heap.
    MaxHeap(const MaxHeap<T> &other) {
        size = other.size;
        capacity = other.capacity;
        array = new T[capacity];
        for (int i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
    }

    // Releases the dynamic memory used by the heap.
    ~MaxHeap() {
        delete[] array;
        array = nullptr;
    }

    // Replaces this heap with a copy of another heap.
    MaxHeap &operator=(const MaxHeap<T> &other) {
        if (this == &other)
            return *this;
        delete[] array;

        size = other.size;
        capacity = other.capacity;
        array = new T[capacity];
        for (int i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
        return *this;
    }

    // Inserts a value into the heap and restores the heap order.
    void push(const T& element) {
        if (size == capacity) {
            expand_capacity();
        }
        array[size++] = element;
        _heapify_up(size - 1);
    }

    // Removes the smallest value from the heap.
    void pop() {
        assert(!is_empty());
        array[0] = array[--size];
        _heapify_down(0);
    }

    // Returns the smallest value without removing it.
    T top() const {
        assert(!is_empty());
        return array[0];
    }

    // Returns true when the heap contains no elements.
    bool is_empty() const{
        return (size == 0);
    }
};

#endif