#include <iostream>

/*
In this exercise, we will implement heap as discussed in the class.
We need to implement the following functions.


ONLY THIS FILE MUST BE MODIFIED FOR SUBMISSION

You may edit main.cpp for writing more test cases.
But your code must continue to work with the original main.cpp


THERE IS ONLY ONE TEST CASE ONLY FOR YOUR UNDERSTANDING.

-- You may need to generate more random tests to get your tests right
-- Print will not work until you have a good printing function
*/


#include "heap.h"


int Heap::parent(int i) {
  return (i - 1) / 2; // dummy return
}

int Heap::left(int i) {
  return 2*i + 1; // dummy return
}

int Heap::right(int i) {
  return 2*i + 2; //dummy
}

int Heap::max() {
  return store[0]; //dummy
}

void Heap::swap(int i, int j) {
  int temp = store[i];
  store[i] = store[j];
  store[j] = temp;
}

void Heap::insert(int v) {
  append(v);
  int i = sz - 1;
  while (i > 0 && store[parent(i)] < store[i]) {
    swap(i, parent(i));
    i = parent(i);
  }
}

void Heap::heapify(int i) {
  int largest = i;
  if (left(i) < sz && store[left(i)] > store[i]) 
        largest = left(i); 
    if (right(i) < sz && store[right(i)] > store[largest]) 
        largest = right(i); 
    if (largest != i) { 
        swap(i, largest); 
        heapify(largest);
    }
}


void Heap::deleteMax() {
  int root = store[0]; 
  store[0] = store[sz - 1]; 
  sz--;
  heapify(0);
}

void Heap::buildHeap() {
  for(int i = sz - 1; i >= 0; i--){
    heapify(i);
  }
}

void Heap::heapSort() {
  buildHeap();
  while(sz > 0) {
    deleteMax();
  }
}


