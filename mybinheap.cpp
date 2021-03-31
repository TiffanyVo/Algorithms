//-----------------------------------------------
// header file for Binary Heap ADT
// 
// mybinheap.h
//------------------------------------------------
#include "mybinheap.h"
#include <iostream>

#define DEFAULT_CAPACITY 1000 // default capacity is 1,000 elements
#define PARENT(i) (i >> 1) // (i / 2) for parent node of i in BH
#define LEFT(i) (i << 1) // (2i) for left child of i in BH
#define RIGHT(i) ((i << 1) + 1) // (2i + 1) for right child of i in BH
using namespace std;

//
// default constructor
//
BinHeap::BinHeap() {
  capacity = DEFAULT_CAPACITY;
  A = new int[capacity + 1]; // A[0] is not used
  size = 0; // no elements thus far
  return;
}

//
// constructor: builds heap with argument capacity
BinHeap::BinHeap(int c) {

  // do not allow capacity smaller than the default 
  if (capacity <= DEFAULT_CAPACITY) {
    cerr << "Warning: Capacity of " << c << " passed to constructor. Binary Heap created with default capacity.\n";
    capacity = DEFAULT_CAPACITY;
  }
  
  // create array for heap.
  A = new int[capacity + 1];
  size = 0; // no elements thus far
  return;
}

//
// constructor: builds heap out of array of integers
//
BinHeap::BinHeap(int *nums, int numNums) {

  // if argument array is larger than default capacity, accomodate
  if (numNums >= DEFAULT_CAPACITY) {
    capacity = DEFAULT_CAPACITY * 2;
  } else {
      capacity = DEFAULT_CAPACITY;
  }
  
  // create array for heap
  A = new int[capacity + 1];
  size = numNums; // numNums elements thus far
  
  // copy over array elements
  for (int i = 0; i < numNums; i++) {
    A[i + 1] = nums[i];
  }
  
  // heapify() non-trivial trees
  for (int i = (size / 2); i >= 1; i--) {
    heapify(i);
  }
  return;
}

//
// destructor
BinHeap::~BinHeap() {
  delete[] A;
}

//
// inserts argument integer into heap
//
void BinHeap::insert(int element) {
  cout << "inserting " << element << endl;
  // safety net
  if (size > capacity) {
    cerr << "Error: size of heap greater than capacity of heap\n";
    exit(EXIT_FAILURE);
  }
  
  // if heap is at maximum capacity, double size of array
  if (size == capacity) {
    resize(2 * capacity);
  }
  
  
  // insert element at end
  A[size + 1] = element;
  cout << "element inserted at index " << size + 1 << endl;
  size++;
  // move element up to appropriate level
  swim(size);
  return;
}

//
// increases the capacity of the heap of argument capacity
//
void BinHeap::resize(int newCapacity) {
  
  // if new capacity is smaller than old capacity
  if (newCapacity < capacity) {
    cerr << "Warning: heap resized to smaller capacity\n";
    newCapacity = DEFAULT_CAPACITY;
  }
  
  // store pointer to old array
  int *old = A;
  // allocate memory for array with new capacity
  A = new int[newCapacity + 1];
  // update capacity
  capacity = newCapacity;

  // copy over old elements
  for (int i = 1; i <= size; i++) {
    A[i] = old[i];
  }
  
  // delete the old array
  delete[] old;
  
  return;
}

//
// RECURSIVE
// makes node "swim" up the heap until it follows the max-heap property
// A[i] > A[left child] AND A[i] > A[right child]
//
void BinHeap::swim(int index) {

  // indices less than 1 or greater than size are not valid in a heap
  if (index < 1 || index > size) {
    cerr << "Error: invalid index passed to swim(): "<< index << endl;
    exit(EXIT_FAILURE);
  }
  
  // BASE CASE: index is 1 or MHP is met.
  if (index == 1 || A[PARENT(index)] >= A[index]) {
    cout << "element swam up to index " << index << endl;
    return;
  }
  
  // node swims up 1
  int fish = A[index]; // store element to be swapped
  A[index] = A[PARENT(index)];
  A[PARENT(index)] = fish;
  
  // recursive call at parent
  swim(PARENT(index));
  
}

//
// returns max value in the heap
//
int BinHeap::findMax() {
  if (size == 0) {
    cout << "query to find maximum invalid, heap is empty...\n";
    return -1;
  } else {
      return A[1]; // MHP
  }
}

//
// ensures that the tree rooted at argument index is a valid heap
//
void BinHeap::heapify(int root) {
  
  
  // if subtree root is beyond size, return!
  if (root >= size) {
    return;
  }
  
  // get left and right children of root
  int left = LEFT(root);
  int right = RIGHT(root);
  int largest = root;
  
  // find the largest element
  if (left <= size && A[left] > A[largest]) { // if left is a valid index AND element is bigger
    largest = left;
  }
  if (right <= size && A[right] > A[largest]) { // if right is a valid index AND element is bigger
    largest = right; 
  }
  
  // if necessary, swap the root with largest and heapify the tree rooted @ that index.
  if(largest != root) {
    int fish = A[root];
    A[root] = A[largest];
    A[largest] = fish;
    heapify(largest);
  }
  
  return;
}

//
// removes the maximum element from the heap, ensuring the new heap is a valid max-heap
//
int BinHeap::extractMax() {

  // removing the max from a 0 or 1 element heap doesn't make sense
  if (size <= 1) {
    cerr << "Warning: heap is of size " << size << " upon call to extractMax()\n";
  }
  
  // swap max with the last element
  int max = A[1];
  A[1] = A[size];
  heapify(1); // heapify() the invalidaded heap
  size--;
  
  return max;
}

//
// returns if the heap is empty
//
bool BinHeap::isEmpty() {
  return (size == 0);
}

// 
// prints heap in order, as array
//
void BinHeap::printHeap() {

  cout << endl << "The size of the heap is: "<< size << endl;
  cout << "The maximum of the heap is: " << findMax() << endl;
  for (int i = 1; i <= size; i++) {
    cout << A[i] << ' ';
  }
  cout << endl << "-----------------------------------" << endl;
}

int main(void) {

  cout << "Learning about Binary Heaps... \n"; // yay!
  BinHeap love; // create heap to play with
  love.printHeap();
  
  love.insert(3); // insert some elements;
  love.printHeap();
  
  for (int i = 4; i < 9; i += 2) {
    love.insert(i);
    love.printHeap();
    love.insert(i-1);
    love.printHeap();
  } 
  
  int myArray[10];
  for (int i = 0; i < 10; i++) {
    myArray[i] = i;
  }
  
  BinHeap more(myArray, 10);
  more.printHeap();
  
  while(!more.isEmpty()) {
    cout << "Maximum extracted: " << more.extractMax() << endl;
    more.printHeap();
  }
  
  return 0;
}
