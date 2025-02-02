#include <iostream>

// Consider the binary search algorithm presented in class. We are interested
// in determining the average execution time of the binary search. To
// accomplish this, let's conduct an experiment.

// Suppose we have an array of size 1024, which contains distinct elements
// arranged in non-increasing order. We have already analyzed the running
// time when the element being searched for is not present in the array.
// Now, let's assume that we are only searching for elements that we know
// exist in the array.

// Our goal is to experimentally calculate the average number of
// iterations required to search for all 1024 elements in the array.

// In the following,
//   -- Implement BinarySearch that can handle non-increasing array
//   -- Harness BinarySearch such that we can compute avarage number
//      of iterations


int BinarySearch ( int * S , int n , int e ) {
  int iteration_count = 0;
  int first = 0, last = n;
  while(first < last) {
    int mid = (first + last) / 2;
    iteration_count++;
    if (S[mid] == e) return mid;
    if (S[mid] < e) {first = mid + 1;}
    else {last = mid-1;}
  }
  // Implement binary search here
  // instead of returning position return the number
  // of executed iterations of binary search.
  return iteration_count;
}

int main() {
  unsigned size = 1024;
  int S[size];
  float average = 0;
  // Initialize array S with distinct elements
  for(int i = size; i > 0; i--) {
    S[i] = size - i;
  }
  int iteration_count = 0;
  for(int i = 0; i < size ; i++) {
    iteration_count += BinarySearch(S,size,S[i]);
  }
  average = (float(iteration_count)) / (float(size));
  // search 1024 element stored in S and compute
  // the average number of iterations in binary search
  
  std::cout << "Average: " << average << "\n";
  return 0;
}
