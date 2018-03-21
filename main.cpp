// main.cpp file
/*
  Author: Aryan Gupta
  Date: 2/11/18
  The program takes an infix expression as input and converts it to postfix using the shunting yard-
  algorithm, then converts it to a binary tree expression in infix, postfix, or prefix
 */

#include "Node.h"
#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

// function prototypes

// prints out tree in infix
void BinaryIn(Node* head);
// prints out tree in postfix
void BinaryPost(Node* head);
// prints out tree in prefix
void BinaryPre(Node* head);
// pops out top Node in the stack
char* pop(Node*& stack);
// pushes a Node in the stack
void push(Node*& stack, char* input);
// reveals top Node in the stack
char* peak(Node*& stack);

int main() {

  // terminate program when user wants to exit
  bool terminate = false;
  
  while(terminate == false) {

    // stack
    Node* stack = new Node();

    // precedence
    map<char, int> operaters;
    operaters['-'] = 2;
    operaters['+'] = 2;
    operaters['*'] = 3;
    operaters['/'] = 3;
    operaters['^'] = 4;

    // associativity
    map<char, int> associativity;
    associativity['^'] = 1;
    associativity['*'] = 0;
    associativity['/'] = 0;
    associativity['-'] = 0;
    associativity['+'] = 0;

    // takes infix expression here
    char* expression = new char[100];
    cout << "Enter an infix expression with spaces between each token: ";
    cin.getline(expression, 100);
    // seperate into vector
    vector<char*> expressionV;
    vector<char*> output;
    char* token = strtok(expression, " ");
    while(token != NULL) {
      expressionV.push_back(token);
      token = strtok(NULL, " ");
    } 
    // iterate through vector
    for(vector<char*>::iterator i = expressionV.begin(); i != expressionV.end(); advance(i, 1)) {
      // Shunting Yard!!!!
      // if the token is a digit
      if(isdigit(*(*i))) {
	output.push_back(*i);
      }
      else if(*(*i) == '+' || *(*i) == '-' || *(*i) == '*' || *(*i) == '/' || *(*i) == '^') {
	while(true) {
	  if(stack->getData() == NULL) {
	    break;
	  }
	  else if(*peak(stack) != '(') {
	    if(operaters[*(*i)]<operaters[*peak(stack)]) {
	      output.push_back(pop(stack));
	    }
	    else if(operaters[*(*i)] == operaters[*peak(stack)] && associativity[operaters[*peak(stack)]] == 0) {
		output.push_back(pop(stack));
	    }
	    else {
	      break;
	    }
	  } // else if(*peak(stack) != '(')
	  else {
	    break;
	  }
	} // while(true)
	push(stack, *i);
      } // else if(*(*i) == '+' || *(*i) == '-' ||...)
      else if(*(*i) == '(') {
	push(stack, *i);
      }
      else if(*(*i) == ')') {
	while(*peak(stack) != '(') {
	  output.push_back(pop(stack));
	}
	pop(stack);
      }
    } // for(vector<char*>::iterator i = expressionV.begin(); i != expressionV.end(); advance(i, 1))
    while(true) {
      if(stack->getData() == NULL) {
	break;
      }
      else {
	output.push_back(pop(stack));
      }
    }
    // iterate through output vector and print expression in postfix
    cout << "Postfix: ";
    for(vector<char*>::iterator it = output.begin(); it != output.end(); advance(it, 1)) {
      cout << *it << " ";
    }
    cout << "  " << endl;

    // stack for binary tree
    vector<Node*> treeStack;
    Node *treeHead, *leaf1, *leaf2;
    //while(terminate == false) {
      // iterate through the postfix expression and make tree
      for(vector<char*>::iterator i = output.begin(); i != output.end(); advance(i, 1)) {
	if(isdigit(*(*i))) {
	  Node* temp = new Node();
	  temp->setData(*i);
	  treeStack.push_back(temp);
	}
	else if(*(*i) == '+' || *(*i) == '-' || *(*i) == '*' || *(*i) == '/' || *(*i) == '^') {
	  // make new Node and connect branches
	  treeHead = new Node();
	  treeHead->setData(*i);

	  leaf1 = treeStack.back();
	  treeStack.pop_back();
	  leaf2 = treeStack.back();
	  treeStack.pop_back();

	  treeHead->setRight(leaf1);
	  treeHead->setLeft(leaf2);
	  treeStack.push_back(treeHead);
	}
      } // for(vector<char*>::iterator i = output.begin(); i != output.end(); advance(i, 1))
      treeHead = treeStack.back();
      treeStack.pop_back();
      bool quit = false;
      while (quit == false) {
	// input to output based on user input
	char* input = new char[8];
	cout << "Convert to INFIX, POSTFIX, or PREFIX? (Type QUIT to exit) ";
	cin.getline(input, 8);
	if(strcmp(input, "INFIX") == 0) {
	  BinaryIn(treeHead);
	  cout << endl;
	}
	else if(strcmp(input, "POSTFIX") == 0) {
	  BinaryPost(treeHead);
	  cout << endl;
	}
	else if(strcmp(input, "PREFIX") == 0) {
	  BinaryPre(treeHead);
	  cout << endl;
	}
	else if(strcmp(input, "QUIT") == 0) {
	  quit = true;
	  terminate = true;
       	}
	else {
	  cout << "Invalid expression type, try again." << endl;
	}
     } // while(terminate == false)
  } // while(terminate = false)
} // int main()

void BinaryIn(Node* head) {
  // if head is NULL
  if(head == NULL) {
    return;
  }
  // if the character is an operator, print a parenthesis
  if(*head->getData() == '+' || *head->getData() == '-' || *head->getData() == '*' || *head->getData() == '/' || *head->getData() == '^') {
    cout << "(";
  }
  // recursively print
  BinaryIn(head->getLeft());
  cout << head->getData();
  BinaryIn(head->getRight());
  // print closing parenthesis
  if(*head->getData() == '+' || *head->getData() == '-' || *head->getData() == '*' || *head->getData() == '/' || *head->getData() == '^') {
    cout << ")";
  } 
} // BinaryIn()

void BinaryPost(Node* head) {
  // if head is NULL
  if(head == NULL) {
    return;
  }
  // recursively print left and right Nodes
  BinaryPost(head->getLeft());
  BinaryPost(head->getRight());
  cout << head->getData();
} // BinaryPost()

void BinaryPre(Node* head) {
  // if head is NULL
  if(head == NULL) {
    return;
  }
  // recursively print
  cout << head->getData();
  BinaryPre(head->getLeft());
  BinaryPre(head->getRight());
} // BinaryPost()

char* pop(Node*& stack) {
  // create temp and return
  char* temp = stack->getData();
  
  if(stack->getRight() != NULL) {
    stack = stack->getRight();
  }
  else {
    stack->setData(NULL);
  }
  return temp;
} // pop()

void push(Node*& stack, char* input) {
  // new head -> old head
  if(stack->getData() != NULL) {
    Node* newNode = new Node();
    newNode->setData(input);
    newNode->setRight(stack);
    stack = newNode;
  }
  else {
    stack->setData(input);
  }
} // push()

char* peak(Node*& stack) {
  if(stack->getData() != NULL) {
    return stack->getData();
  }
  else {
    return NULL;
  }
} // peak()
