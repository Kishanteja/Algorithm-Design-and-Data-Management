#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return size() == 0; // dummy return
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return size() == N; // dummy return
}

template <typename T> void DynamicQueue<T> :: grow() {
  if(isFull()) {
    unsigned int old_size = N;
    N = nextSize();
    T* new_queue = new T[N];
    for(int i=0; i<old_size; i++) {
      new_queue[i] = A[i];
    }
	delete[] A;
	A = new_queue;
  }else
  return;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return tail - head; // dummy return
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
	if (tail == N) {
    if (head > 0)
    {
      for(int i=head; i<tail; i++)
          A[i-head]=A[i];
        tail-=head;
        head=0;
    }
    else
    grow();
   /* code */
  }
  A[tail] = x;
  tail++;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  if(isEmpty())
      return false;
    *x = A[head];
    head ++;
  return true; // dummy return
}
