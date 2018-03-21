// Node.h file
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;

class Node {
 public:
  Node(); // constructor
  ~Node(); // destructor

  // getters
  Node* getLeft();
  Node* getRight();
  char* getData();
  // setters
  void setLeft(Node* newLeft);
  void setRight(Node* newRight);
  void setData(char* newData);
 private:
  // member variables
  Node* left;
  Node* right;
  char* data;
};
#endif
