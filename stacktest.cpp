//--------------------------------------------
//
// source file
//
// stacktest.cpp
//--------------------------------------------
#include "list.h" // provided by Sesh
#include <iostream>
#include <stack>
#include <string>

using namespace std;

//
// struct for stretch
struct frame {
  int pos; // to track pogress along string
  string str; // to hold unfinished string
};

//
// returns a List of all strings with each character stretched up to k times
//
List stretch(string input, int k) {

  // CREATE LIST FOR STRETCHED STRINGS
  List results;
  
  // CREATE STACK + PUSH FIRST FRAME
  stack<frame> callstack;
  frame job;
  job.pos = 0; // start at index 0 of input string
  job.str = ""; // begin with an empty string
  callstack.push(job);
  
  // STACK-BASED RECURSION
  while (!callstack.empty()) {
  
    // get top job
    job = callstack.top();
    callstack.pop();
    if (job.pos == (int) input.length()) {
      results.insert(job.str); // if all characters in input have been added to the frame's string, ADD TO LIST
    } else {
        frame newJob; // create new frame
        newJob.str = job.str; // copy over old frame's string
        for (int stretched = 1; stretched <= k; stretched++) { \
          newJob.str += input[job.pos]; // append character at pos of input
          newJob.pos = job.pos + 1; // the string is ready for the next character of input 
          callstack.push(newJob); // PUSH 
      }
    }
  }
  return results;
}

//
// returns a list of all subsets of string s of up to size k
//
List language(string input, int k) {
  
  // CREATE LIST 
  List results;
  
  // CREATE STACK + PUSH EMPTY STRING
  stack<string> callstack;
  callstack.push("");
  
  // STACK-BASED RECURSION
  while (!callstack.empty()) {
  
    // get string from stack
    string str = callstack.top();
    callstack.pop();
    
    // add string to list
    results.insert(str);
    
    // add chars from input
    if ((int) str.length() < k) {
    
      for (int i = 0; i < (int) input.length(); i++) {
        str += input[i]; // add a char from input string
        callstack.push(str); // push the new string
        str.pop_back(); // remove to add the next char from input
      }
      
    }
   
  }
  return results;
}

struct Pair {
  string anag; // for building the anagram
  string options; // characters left to choose from
};

//
// returns a list of all anagrams of input string
//
List allAnagrams(string input) {
  
  // CREATE LIST
  List results;
  
  // CREATE STACK
  stack<Pair> callstack;
  Pair first;
  
  // PUSH EMPTY STRING
  first.anag = ""; // begin with empty string
  first.options = input; // options are all chars in input
  callstack.push(first);
  
  // STACK-BASED RECURSION
  while (!callstack.empty()) {
  
    // get top pair of strings
    Pair top = callstack.top();
    callstack.pop();
    
    // if there are no options left, anagram is complete
    if (top.options.length() == 0) {
      results.insert(top.anag);
    } else {
        for (int i = 0; i < (int) top.options.length(); i++) { // append every character
          Pair newpair = top; // copy old string and options into new pair
          newpair.anag += top.options[i]; // append a character from options
          newpair.options = top.options;// remove character from options
          newpair.options.erase(i, 1);
          callstack.push(newpair); // push new pair
        }
    }
  }
  
  return results;
}

int main() {

  // TEST STRETCH
  List myList = stretch("abc", 2);
  cout << myList.print() << endl;
  
  // TEST LANGUAGE
  List myOtherList = language("abc", 2);
  cout << myOtherList.print() << endl;
  
  myOtherList = language("aA", 2);
  cout << myOtherList.print() << endl;
  
  // TEST allAnagrams
  myList = allAnagrams("abc");
  cout << myList.print() << endl;
  myList = allAnagrams("aaa");
  cout << myList.print() << endl;
  
  return 0;
}
