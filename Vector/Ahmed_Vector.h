#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cassert>
using namespace std;

template <class T>

class Vector {
private:
  int size = 0;     // current number of elements stored
  int capacity = 4; // allocated storage capacity (initial)
  T *arr = nullptr; // pointer to dynamic array holding elements

  using iterator = T *; // iterator type alias (raw pointer)

  void expand_capacity() {           // double capacity and reallocate storage
    capacity *= 2;                   // double the capacity
    T *arr2 = new T[capacity];       // allocate new array with larger capacity
    for (int i = 0; i < size; ++i) { // copy existing elements to new array
      arr2[i] = arr[i];              // copy element i
    }
    swap(arr, arr2); // swap pointers so `arr` points to new storage
    delete[] arr2;   // delete old storage (now in arr2)
  }

public:
  Vector() {               // default constructor
    arr = new T[capacity]; // allocate initial array with `capacity`
  }

  Vector(int size) : size(size) { // constructor that sets initial size
    if (size <= 0)
      size = 1; // ensure a minimum size of 1

    capacity = size + 10;  // set capacity larger than requested size
    arr = new T[capacity]; // allocate array with chosen capacity
  }

  Vector(const Vector &other) { // copy constructor (deep copy)
    size = other.size;
    capacity = other.capacity;
    arr = new T[capacity]; // allocate new storage
    for (int i = 0; i < size; ++i) {
      arr[i] = other.arr[i]; // copy each element
    }
  }

  Vector &operator=(const Vector &other) { // copy assignment operator
    if (this == &other)
      return *this; // handle self-assignment
    delete[] arr;   // free current storage

    size = other.size;
    capacity = other.capacity;
    arr = new T[capacity]; // allocate new storage
    for (int i = 0; i < size; ++i) {
      arr[i] = other.arr[i]; // copy elements
    }
    return *this; // return assigned object
  }

  int get_size() const { // return number of elements
    return size;
  }

  T get(const int &index) const { // get element by value with bounds check
    assert(index >= 0 && index < size); // ensure index valid
    return arr[index];
  }

  void set(const int &index, const T &value) { // set element with bounds check
    assert(index >= 0 && index < size);
    arr[index] = value;
  }

  void insert(const int &index, const T &value) { // insert value at given index
    assert(index >= 0 && index < size);
    if (size == capacity)
      expand_capacity(); // expand if array full

    for (int i = size - 1; i >= index; --i) {
      arr[i + 1] = arr[i]; // shift elements right to make room
    }
    arr[index] = value; // place new value
    ++size;             // increase size
  }

  void push_back(const T &value) { // append value to end
    if (size == capacity)
      expand_capacity(); // expand if needed
    arr[size++] = value; // place value and increment size
  }

  T get_front() const { // return first element (no assert)
    return arr[0];
  }

  T get_back() const { // return last element (no assert)
    return arr[size - 1];
  }

  iterator begin() const { // iterator to first element
    return arr;
  }

  iterator end() const { // iterator one-past-last element
    return arr + size;
  }

  void pop_back() {   // remove last element
    assert(size > 0); // ensure not empty
    --size;           // just decrement size
  }

  int find(const T &value) const { // linear search for `value`
    for (int i = 0; i < size; ++i) {
      if (arr[i] == value)
        return i; // return index of first match
    }
    return -1; // not found
  }

  bool empty() const { // check if container empty
    return (size == 0);
  }

  T &operator[](const int index) { // subscript operator (returns reference)
    assert(index >= 0 && index < size); // bounds check
    return arr[index];
  }

  void erase(const int &index) {        // erase element at index
    assert(index >= 0 && index < size); // bounds check
    for (int i = index; i < size - 1; ++i) {
      arr[i] = arr[i + 1]; // shift elements left to fill gap
    }
    --size; // decrease size
  }

  ~Vector() {     // destructor
    delete[] arr; // free allocated array
    arr = nullptr;
  }
};

#endif