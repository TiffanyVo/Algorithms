//--------------------------------------------
// TEST 1 PRACTICE
//
// source file
//
// linktest.cpp
//--------------------------------------------
#include "linktest.h"
#include <iostream>
#include <string>


using namespace std;

//
// default constructor
//
LinkedList::LinkedList() {
  head = nullptr;
}

//
// destructor (frees memory)
//
LinkedList::~LinkedList() {
  while (head != nullptr) {
    Node *node = head;
    head = head->next;
    delete node;
  }
}

//
// inserts value at head
//
void LinkedList::insert(int value) {
  Node *newNode = new Node;
  newNode->data = value;
  newNode->next = head;
  head = newNode;
}

//
// returns pointer to Node corresponding to value
//
Node *LinkedList::find(int value) {
  Node *node = head;
  while (node != nullptr && node->data != value) {
    node = node->next;
  }
  return node;
}

//
// removes first corresponding Node, returns pointer to it
// H is the node to begin search at, typically the head
//
Node *LinkedList::remove(Node *H, int value) {

  Node *prev = nullptr;
  Node *node = H;
  while (node != nullptr && node->data != value) {
    prev = node;
    node = node->next;
  }
  
  if (node == nullptr) {
    return nullptr;
  }
  
  if (node == head) {
    head = head->next;
  } else {
      prev->next = node->next;
  }
  
  return node;
}

//
// returns length
//
int LinkedList::length() {
  int length = 0;
  Node *node = head;
  while (node != nullptr) {
    length++;
    node = node->next;
  }
  return length;
}

//
// returns string with all list data, separated by spaces
//
string LinkedList::print() {
  string list = "";
  Node *node = head;
  while (node != nullptr) {
    list = list + to_string(node->data) + " ";
    node = node->next;
  }
  if (list.length() > 0) {
    // remove extraneous space
    list.pop_back();
  }
  return list;
}

//
// deletes all duplicates in a list without shuffling order
//
void LinkedList::dedup() {
  Node *node = head;
  Node *prev;
  Node *curr;
  // for every element in the list
  while (node != nullptr) { 
    prev = node;
    curr = node->next;
    while (curr != nullptr) {
      if (curr->data == node->data) {
        Node *duplicate = curr;
        prev->next = curr->next;
        curr = curr->next;
        delete duplicate;
      } else {
          prev = curr;
          curr = curr->next;
      }
    }
    node = node->next;
  }
}

//
// finds the xth Node of a list
//
Node * LinkedList::getNode(int x) {
  if (x > this->length()) {
    cerr << "Error: x passed to getNode() exceeds list size" << endl;
    exit(EXIT_FAILURE);
  }
  int i = 0;
  Node *node = head;
  while (node != nullptr && i != x) {
    node = node->next;
    i++;
  }
  return node;
}

// 
// reverses the first upTo elements of a list,
// reverses all elements if upTo > list length
//
void LinkedList::reverse(int upTo) {

  int len = length();
  
  // empty or list of size 1 already sorted
  if (len < 2) {
    return;
  }
  
  // reverse whole list if request is beyond size
  if (upTo > len) {
    upTo = len;
  }
  
  // for every pair
  for (int left = 0, right = upTo - 1; left < right; left++, right--) {
    // find pointers to the nodes
    Node *leftNode = getNode(left);
    Node *rightNode = getNode(right);
    // swap their data
    int temp = leftNode->data;
    leftNode->data = rightNode->data;
    rightNode->data = temp;
  }
  
  return;
}

//
// returns true if a list is a palindrome
//
bool LinkedList::palindrome(int left, int right) {
  return (left >= right) ? true : (getNode(left)->data == getNode(right)->data) && palindrome(left + 1, right - 1);
}

//
// returns true if a list is a palindrome
//
bool LinkedList::palindrome() {
  return palindrome(0, length() - 1);
}

//
// rotates a list by x spots
//
void LinkedList::rotate(int x) {

  // get actual # of spots to rotate
  int n = x % length();
  
  // no rotation necessary
  if (n == 0) {
    return;
  }
  
  // get new tail and head
  Node *newTail = getNode(length() - n - 1);
  Node *newHead = newTail->next;
  
  //merge the lists
  Node *mid = newHead;
  while (mid->next != nullptr) {
    mid = mid->next;
  }
  mid->next = head;
  
  // redefine head
  head = newHead;
  // new tail points to null
  newTail->next = nullptr;
  
}

//
// returns last occurence of element x if it exists
// removes its node from the list
//
Node *LinkedList::deletelast(int x) {
  Node *plast = nullptr;
  Node *last = nullptr;
  Node *prev = nullptr;
  Node *curr = head;
  while (curr != nullptr) {
    if (curr->data == x) {
      plast = prev;
      last = curr;
    }
    prev = curr;
    curr = curr->next;
  }
  
  if (last != nullptr && last == head) {
    head = head->next;
  } else if (last != nullptr) {
      plast->next = last->next;
  }
  last->next = nullptr;
  return last;
}

int main() {

  LinkedList list;
  
  for(int i = 0; i < 6; i++) {
    list.insert(i);
  }
  
  cout << list.print() << endl;
  
  for (int i = 0; i < 6; i++) {
    list.insert(7);
    list.insert(4);
    list.insert(2);
  }
  
  list.insert(2);
  list.insert(2);
  list.insert(2); 
    
  cout << list.print() << endl;
  cout << "THE LIST IS ABOVE" << endl;
  list.dedup();
  cout << "DEDUP HAS BEEN CALLED HERE IS LIST NOW:" << endl ;
  cout << list.print() << endl;
  cout << "I AM HERE NOW OK" << endl;
  int len = list.length();
  cout << "HENLO I GOT THE LIST LENGTH IT IS: " << len << endl;
  
  int x = 290;
  list.reverse(x);
  cout << "THE FIRST " << x << " ELEMENTS OF THE LIST ARE REVERSED: " << endl;
  cout << list.print() << endl;
  
  LinkedList b;
  b.insert(3);
  b.insert(7);
  b.insert(2);
  b.insert(2);
  b.insert(2);
  b.insert(1);
  cout << b.print() << endl;;
  cout << b.palindrome() << endl;
  
  list.rotate(9);
  cout << list.print() << endl;
  
  
  b.deletelast(1);
  cout << b.print() << endl;
  
  return 0;
}

