/**
* ---------------------------------------------------------------------------*
 * | File Name   : StackArray.h                                              |*
 * |                                                                         |*
 * | Author      : Ahmed Shawareb                                            |*
 * |                                                                         |*
 * | Email       : eng.ahmedshawareb@gmail.com                               |*
 * |                                                                         |*
 * | Description : Stack implementation for Data Structures (Array).         |*
 * ---------------------------------------------------------------------------*
**/


#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <cassert>

template <typename T>
// Represents a stack implemented using a fixed-size array.
class StackArray {
private:
 int size {};
 int top {};
 T *array {};
public:
 // Creates a stack with the given maximum capacity.
 StackArray(int size) {
  if (size <= 0) {
   size = 1;
  }
  this->size = size;
  array = new T[size];
  top = -1;
 }

 // Creates a copy of another stack by duplicating its stored elements.
 StackArray(const StackArray<T> &other) {
  size = other.size;
  top = other.top;
  array = new T[size];
  for (int i = 0; i <= top; ++i) {
   array[i] = other.array[i];
  }
 }

 // Replaces the current stack contents with a copy of another stack.
 StackArray &operator=(const StackArray<T> &other) {
  if (this == &other)
   return *this;
  delete[] array;

  size = other.size;
  top = other.top;
  array = new T[size];
  for (int i = 0; i <= top; ++i) {
   array[i] = other.array[i];
  }
  return *this;
 }

 // Releases the memory used by the stack.
 ~StackArray() {
  delete[] array;
  array = nullptr;
 }

 // Returns true when the stack has reached its maximum capacity.
 bool isFull() const {
  return (top == size - 1);
 }

 // Returns true when the stack contains no elements.
 bool isEmpty() const {
  return (top == -1);
 }

 // Inserts a value onto the top of the stack.
 void push(T value) {
  assert(!isFull());
  array[++top] = value;
 }

 // Returns the value at the top of the stack without removing it.
 T peek() const {
  assert(!isEmpty());
  return array[top];
 }
 
 // Removes and returns the top element from the stack.
 T pop() {
  assert(!isEmpty());
  return array[top--];
 }
};

#endif
