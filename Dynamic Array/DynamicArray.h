/**
 * ---------------------------------------------------------------------------*
 * | File Name   : DynamicArray.h                                            |*
 * |                                                                         |* 
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |* 
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Dynamic Array(vector) implementation for Data Structures. |*
 * ---------------------------------------------------------------------------*
**/

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <algorithm>
#include <cassert>
using namespace std;

template <class T>
class DynamicArray {
private:
  int size = 0;
  int capacity = 4;
  T *arr = nullptr;

  // Increases the storage capacity and copies the existing elements.
  void expand_capacity() {
    capacity *= 2;
    T *arr2 = new T[capacity];
    for (int i = 0; i < size; ++i) arr2[i] = arr[i];
    delete[] arr;
    arr = arr2;
  }

public:
  // Creates an empty dynamic array with an initial capacity of four elements.
  DynamicArray() { arr = new T[capacity]; }

  // Creates a dynamic array with the requested number of elements.
  DynamicArray(int size) : size(size) {
    if (this->size <= 0)
      this->size = 1;

    capacity = this->size + 10;
    arr = new T[capacity];
  }

  // Creates a deep copy of another dynamic array.
  DynamicArray(const DynamicArray<T> &other) {
    this->size = other.size;
    this->capacity = other.capacity;
    arr = new T[capacity];
    for (int i = 0; i < size; ++i) {
      this->arr[i] = other.arr[i];
    }
  }

  // Releases the memory used by the dynamic array.
  ~DynamicArray() {
    delete[] arr;
    arr = nullptr;
  }

  // Returns a modifiable reference to the element at the specified index.
  T &operator[](const int index) {
    assert(index >= 0 && index < size);
    return arr[index];
  }

  // Replaces this array with a deep copy of another dynamic array.
  DynamicArray &operator=(const DynamicArray<T> &other) {
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

  // Returns the number of elements currently stored in the array.
  int get_size() const { return size; }

  // Returns the element at the specified index.
  T get(const int &index) const {
    assert(index >= 0 && index < size);
    return arr[index];
  }

  // Updates the element at the specified index with a new value.
  void set(const int &index, const T &value) {
    assert(index >= 0 && index < size);
    arr[index] = value;
  }

  // Inserts a value at the specified index and shifts later elements right.
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

  // Adds a value to the end of the array.
  void push_back(const T &value) {
    if (size == capacity)
      expand_capacity();
    arr[size++] = value;
  }

  // Returns the first element in the array.
  T get_front() const {
    assert(size > 0);
    return arr[0];
  }

  // Returns the last element in the array.
  T get_back() const {
    assert(size > 0);
    return arr[size - 1];
  }

  // Removes the last element from the array.
  void pop_back() {
    assert(size > 0);
    --size;
  }

  // Finds and returns the index of the first matching value.
  // Returns -1 when the value is not found.
  int find(const T &value) const {
    for (int i = 0; i < size; ++i) {
      if (arr[i] == value)
        return i;
    }
    return -1;
  }

  // Returns true when the array contains no elements.
  bool is_empty() const { return (size == 0); }

  // Removes the element at the specified index and shifts later elements left.
  void erase(const int &index) {
    assert(index >= 0 && index < size);
    for (int i = index; i < size - 1; ++i) {
      arr[i] = arr[i + 1];
    }
    --size;
  }

};

#endif