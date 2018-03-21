// Node.cpp file
#include "Node.h"
#include <cstring>

Node::Node() {
  left = NULL;
  right = NULL;
  data = NULL;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

char* Node::getData() {
    return data;
}

void Node::setLeft(Node* newLeft) {
  left = newLeft;
}

void Node::setRight(Node* newRight) {
  right = newRight;
}

void Node::setData(char* newData) {
  data = newData;
}

Node::~Node() {
  delete[] data;
}
  
