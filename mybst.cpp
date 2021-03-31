//--------------------------------------------
// source file for Binary Search Tree ADT
//
// mybst.cpp
//--------------------------------------------
#include "mybst.h"
#include <iostream>
using namespace std;

//
// default constructor
// sets root to NULL
//
BST::BST() {
  root = nullptr;
}

//
// inserts argument integer into BST
// maintains BST property
//
void BST::insert(int number) {

  Node *newNode = new Node(number); // create new Node
  
  cout << "Node inserted with value : " << newNode->key << endl;
  // IF TREE IS EMPTY
  if (root == nullptr) {
    root = newNode;
    return;
  }
  
  // OTHERWISE, FIND PLACEMENT
  Node *prev = nullptr;  // trailing pointer, for parent assignment 
  Node *curr = root;  // begin transversal at root

  while(curr != nullptr) {
    prev = curr; // update trailing pointer
    // step down in appropriate direction
    if (newNode->key <= curr->key) {
      curr = curr->left; // step down to LEFT
    } else {
        curr = curr->right; // step down to RIGHT
    }
  }
  
  // INSERT NODE
  newNode->parent = prev; // assign parent to the Node
  if (newNode->key <= prev->key) { // assign the Node to parent
    prev->left = newNode;
  } else {
      prev->right = newNode;
  }
  
  return; // done! 
}

//
// returns pointer to node with smallest key
//
Node *BST::min(Node *x) {
  while (x != nullptr && x->left != nullptr) {
    x = x->left;
  }
  return x;
}

//
// returns pointer to node with largest key
//
Node *BST::max(Node *x) {
  while (x != nullptr && x->right != nullptr) {
    x = x->right;
  }
  return x;
}

//
// returns pointer to node with largest key smaller than that of x
// assumes x is a valid pointer
//
Node *BST::predecessor(Node *x) {
  
  // if the left subtree exists, return its maximum.
  if (x->left != nullptr) {
    return max(x->left);
  }
  
  // otherwise, the predecessor of x is the parent of the rightmost ancestor of x
  // recall a node can be an ancestor of itself
  Node *pred = x->parent;
  while (pred != nullptr && x == pred->left) {
    x = pred;
    pred = pred->parent;
  }
  return pred;
}

//
// returns pointer to node with smallest key larger than that of x
// assumes x is a valid pointer
//
Node *BST::successor(Node *x) {
  
  // if the right subtree exists, return its minimum.
  if (x->right != nullptr) {
    return min(x->right);
  }
  
  // otherwise, the successor of x is the parent of the leftmost ancestor of x
  // recall a node can be an ancestor of itself
  Node *succ = x->parent;
  while (succ != nullptr && x == succ->right) {
    x = succ;
    succ = succ->parent;
  }
  return succ;
}

//
// returns pointer to Node with argument key if it exists
// returns NULL otherwise
//
Node *BST::find(int k) {

  // binary search
  Node *x = root; // begin search at root of BST
  while (x != nullptr && x->key != k) {
    if (k < x->key) {
      x = x->left; // search left-rooted subtree
    } else {
        x = x->right; // search right-rooted subtree
    }
  }
  return x;
}


//
//
void BST::printInOrder() {
  cout << "PRINTING TREE inorder: \n";
  cout << "ROOT HAS VALUE: " << root->key << endl;
  printInOrder(root);
  cout << "DONE PRINTING TREE\n";
  return;  
}

//
//
void BST::printInOrder(Node *x) {
  if (x != nullptr) {
    printInOrder(x->left);
    cout << x->key << endl;
    //cout << x->key << endl;
    printInOrder(x->right);
  }
}

//
// prints tree in PRE order
//
void BST::printPreOrder() {
  cout << "PRINTING TREE in preorder: \n";
  cout << "ROOT HAS VALUE: " << root->key << endl;
  printPreOrder(root);
  cout << "DONE PRINTING TREE\n";
  return;  
}

//
// recursive function for PRE order
//
void BST::printPreOrder(Node *x) {
  if (x != nullptr) {
    cout << x->key << endl;
    printPreOrder(x->left);
    printPreOrder(x->right);
  }
}


//
// helper function for lca
// assumes # of steps is valid 
//
Node *stepUp(Node *n, int steps) {
  while (steps > 0) {
    n = n->parent;
    steps--;
  }
  return n;
}

//
// returns pointer to least common ancestor of two values.
// returns NULL if such node doesn't exist
//
Node *BST::badLca(int key1, int key2) {
  
  
  // FIND NODE AND DEPTH OF KEY 1:
  Node *node1 = root; // begin search at root of BST
  int depth1 = 0;
  while (node1 != nullptr && key1 != node1->key) {
    if (key1 < node1->key) {
      node1 = node1->left; // search left-rooted subtree
    } else {
        node1 = node1->right; // search right-rooted subtree
    }
    depth1++;
  }
  
  // EDGE CASES: IF NO SUCH NODE EXISTS, IF KEYS ARE THE SAME
  if (node1 == nullptr) {
    return nullptr; // does not exist in BST
  } else if (key1 == key2) {
      return node1; // LCA of a node and itself is the node
  }
  
  // FIND NODE AND DEPTH OF KEY 2
  Node *node2 = root; // begin search at root of BST
  int depth2 = 0;
  while (node2 != nullptr && key2 != node2->key) {
    if (key2 < node2->key) {
      node2 = node2->left; // search left-rooted subtree
    } else {
        node2 = node2->right; // search right-rooted subtree
    }
    depth2++;
  }
  
  // EDGE CASES: IF NO NODE FOR KEY 2 EXISTS
  if (node2 == nullptr) {
    return nullptr;
  }
  
  // FIND THEIR LCA
  Node *a;
  Node *b;
  if (depth1 > depth2) { // node 1 is at lower level
    a = node2; 
    b = stepUp(node1, depth1 - depth2);
  } else if (depth2 > depth1) { // node 2 is at lower level
      a = node1;
      b = stepUp(node2, depth2 - depth1); // nodes are on same levele
  } else {
      a = node1;
      b = node2;
  }
  
  while (a != b) {
    a = a->parent;
    b = b->parent;
  }
  
  return a;
  
}

//
//
Node *BST::lca(int a, int b) {

  // if either node doesn't exist, return
  if (find(a) == nullptr || find(b) == nullptr) {
    return nullptr;
  }
  
  // find the lca
  Node *node = root;
  while((node->key < a && node->key < b) || (node->key > a && node->key > b)) {
    if (node->key < a && node->key < b) {
      node = node->right;
    } else {
        node = node->left;
    }
  }
  return node;
}


//
// returns # of nodes in BST
//
int BST::size(Node *start) {
  return (start == nullptr) ? 0 : (1 + size(start->left) + size(start->right));
}

//
// returns width of the tree: the # of nodes @ the largest level
//
int BST::width() {
  
  // if tree is empty
  if (root == nullptr) {
    return 0;
  }
  
  int numNodes = size(root);
  
  int *widths = new int[numNodes]; // worst case tree is a linkedlist
  
  // initialize to 0
  for (int i = 0; i < numNodes; i++) {
    widths[i] = 0;
  }
  
  // get widths of each level
  width(root, 0, widths);
  int girthiest = 0;
  for (int i = 0; i < numNodes; i++) {
    if (widths[i] > girthiest) {
      girthiest = widths[i];
    }
  }
  return girthiest;
}

//
// reeeeeeecursion :DDD rawr Liam doesn't like using up paper. Today Liam is fine, he supposes,
// as he rushes to copy physics solutions down into his low quality notebook. He sighs. It wasn't
// meant to be this way...
//
void BST::width(Node *node, int depth, int *ryan) {
  if (node != nullptr) {
    ryan[depth]++;
    width(node->left, depth + 1, ryan);
    width(node->right, depth + 1, ryan);
  }
}

int main () {
  cout << "Let's test out my Binary Search Tree... \n";
  BST tree;
  /*tree.insert(1);
  tree.printInOrder();
  tree.insert(3);
  tree.printInOrder();
  tree.insert(2);
  tree.printInOrder();
  tree.insert(4);
  tree.printInOrder();
  tree.insert(5);
  tree.printInOrder();
  
  Node *mine = tree.lca(1,5);
  cout << "LCA of 1 and 5 is: " << mine->key << endl;
  
  mine = tree.lca(2,5);
  cout << "LCA of 2 and 5 is: " << mine->key << endl;
  
  mine = tree.lca(5,5);
  cout << "LCA of 5 and 5 is: " << mine->key << endl;
  */
  for (int i = 0; i < 356; i++) {
    tree.insert(i);
  }
  
  cout << "Width of my tree is: " << tree.width() << endl;
  
  return 0;
}