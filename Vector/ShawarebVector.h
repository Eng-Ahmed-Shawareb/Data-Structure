/**
 * ---------------------------------------------------------------------------*
 * | File Name   : ShawarebVector.h                                          |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Vector implementation for Data Structures.                |*
 * ---------------------------------------------------------------------------*
**/

#ifndef SHAWAREB_VECTOR_H
#define SHAWAREB_VECTOR_H

#include <algorithm>
#include <cassert>
using namespace std;

template <class T>
// Dynamic array implementation with automatic capacity management
class ShawarebVector {
private:
  int size = 0;
  int capacity = 4;
  T *arr = nullptr;

  // Time: O(n), Space: O(n)
  // Doubles capacity and reallocates storage when full
  void expand_capacity() {
    capacity *= 2;
    T *arr2 = new T[capacity];
    for (int i = 0; i < size; ++i) {
      arr2[i] = arr[i];
    }
    swap(arr, arr2);
    delete[] arr2;
  }

public:
  // Time: O(1), Space: O(1)
  // Default constructor initializes with capacity of 4
  ShawarebVector() { arr = new T[capacity]; }

  // Time: O(1), Space: O(1)
  // Constructor that sets initial size with extra capacity
  ShawarebVector(int size) : size(size) {
    if (this->size <= 0)
      this->size = 1;

    capacity = this->size + 10;
    arr = new T[capacity];
  }

  // Time: O(n), Space: O(n)
  // Copy constructor creates deep copy of another vector
  ShawarebVector(const ShawarebVector &other) {
    size = other.size;
    capacity = other.capacity;
    arr = new T[capacity];
    for (int i = 0; i < size; ++i) {
      arr[i] = other.arr[i];
    }
  }

  // Time: O(n), Space: O(1)
  // Assignment operator with self-assignment check
  ShawarebVector &operator=(const ShawarebVector &other) {
    if (this == &other)
      return *this;
    delete[] arr;

    size = other.size;
    capacity = other.capacity;
    arr = new T[capacity];
    for (int i = 0; i < size; ++i) {
      arr[i] = other.arr[i];
    }
    return *this;
  }

  // Time: O(1), Space: O(1)
  int get_size() const { return size; }

  // Time: O(1), Space: O(1)
  T get(const int &index) const {
    assert(index >= 0 && index < size);
    return arr[index];
  }

  // Time: O(1), Space: O(1)
  void set(const int &index, const T &value) {
    assert(index >= 0 && index < size);
    arr[index] = value;
  }

  // Time: O(n), Space: O(1)
  // Shifts elements right to make room for new value
  void insert(const int &index, const T &value) {
    assert(index >= 0 && index <= size);
    if (size == capacity)
      expand_capacity();

    for (int i = size - 1; i >= index; --i) {
      arr[i + 1] = arr[i];
    }
    arr[index] = value;
    ++size;
  }

  // Time: O(1), Space: O(1)
  void push_back(const T &value) {
    if (size == capacity)
      expand_capacity();
    arr[size++] = value;
  }

  // Time: O(1), Space: O(1)
  T get_front() const { return arr[0]; }

  // Time: O(1), Space: O(1)
  T get_back() const { return arr[size - 1]; }

  // Time: O(1), Space: O(1)
  void pop_back() {
    assert(size > 0);
    --size;
  }

  // Time: O(n), Space: O(1)
  // Returns 0-based index of first match, or -1 if not found
  int find(const T &value) const {
    for (int i = 0; i < size; ++i) {
      if (arr[i] == value)
        return i;
    }
    return -1;
  }

  // Time: O(1), Space: O(1)
  bool empty() const { return (size == 0); }

  // Time: O(1), Space: O(1)
  // Subscript operator returns reference for direct element access
  T &operator[](const int index) {
    assert(index >= 0 && index < size);
    return arr[index];
  }

  // Time: O(n), Space: O(1)
  // Shifts elements left to fill gap at erased position
  void erase(const int &index) {
    assert(index >= 0 && index < size);
    for (int i = index; i < size - 1; ++i) {
      arr[i] = arr[i + 1];
    }
    --size;
  }

  // Time: O(1), Space: O(1)
  // Destructor deallocates dynamic array
  ~ShawarebVector() {
    delete[] arr;
    arr = nullptr;
  }
};

#endif