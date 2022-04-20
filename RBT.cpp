#include <iostream>
#include "Node.h"
#include <cstring>
#include <math.h>
#include <fstream>
void printFormat(Node* head, int space);
void addTree(Node* & head, Node* current, Node* newnode);
void searchTree(Node* current, int data);
void fixTree(Node* head);
void leftRotate(Node* & head, Node* target);
using namespace std;
int main() {
  Node* heaparray[100];
  int sizecount = 1;
  Node* treehead = NULL;
  int input = 0;
  bool running = true;
  char commandinput[7];
  //Main loop
  while(running == true){
    cout << "Please enter your input. Enter ADD to add a number to the tree, PRINT to print the tree, SEARCH to search the tree for a number, FILE to load a tree from the file, DELETE to delete the tree, and QUIT to end the program." << endl;
    cin >> commandinput;
    if(strcmp(commandinput, "ADD") == 0) {
       cout << "Insert number" << endl;
       cin >> input;
       Node* newnode = new Node(input);
       addTree(treehead, treehead, newnode);
    }
    else if (strcmp(commandinput, "PRINT") == 0) {
      leftRotate(treehead, treehead->getRight());
      printFormat(treehead, 3);
    }
    else if (strcmp(commandinput, "SEARCH") == 0) {
      cout << "Enter the number you would like to search for: " << endl;
      cin >> input;
      searchTree(treehead, input);
    }
    else if (strcmp(commandinput, "FILE") == 0) {
      //Opens from file and iterates through using the same add function
      fstream File;
      int fileinput = 0;
      File.open("File.txt");
      for(int i = 0; i <100; i++) {
	File >> fileinput;
	Node* newnode = new Node(fileinput);
	addTree(treehead, treehead, newnode);
      }
    }
    else if (strcmp(commandinput, "QUIT") == 0) {
      running = false;
    }
    else {
      cout << "Please enter a valid input" << endl;
    }
  }
  return 0;
}
void addTree(Node* & head, Node* current, Node* newnode) {
  //Sets the new node as head if the tree is empty
  if(head == NULL) {
    head = newnode;
    newnode->changeColor();
    return;
  }
  //Uses the value of the data to determine where it goes in the tree (DOES NOT ACCOUNT FOR DUPLICATES)
  else {
    if(newnode->getData() > current->getData()) {
      if(current->getRight() == NULL) {
	current->setRight(newnode);
	return;
      }
      else {
        addTree(head, current->getRight(), newnode);
      }
    }
    else if(newnode->getData() < current->getData()) {
    if(current->getLeft() == NULL) {
      current->setLeft(newnode);
      return;
    }
    else {
      addTree(head, current->getLeft(), newnode);
    }
    }
    else {
       if(current->getLeft() == NULL) {
           current->setLeft(newnode);
	   newnode->setParent(current);
           return;
       }
       else if(current->getRight() == NULL) {
           current->setRight(newnode);
	   newnode->setParent(current);
            return;
       }
       else {
	 return;
       }
    }
  }
  
}
void printFormat(Node* head, int space) {
  //Same print function from heap
  if (head == NULL) {
    return;
  }
    space = space + 5;
    if(head->getRight() != NULL) {
      
    printFormat(head->getRight(), space);
    }
    cout<<endl;
    for (int i = 0; i < space; i++) {
        cout<<" ";
    }
    head->printNode();
    cout << endl;
    if(head->getLeft() != NULL) {
    printFormat(head->getLeft(), space);
    }
}
void searchTree(Node* current, int data) {
  //Goes through the tree, implementation is a little bit messy
  //The while loop here could just be a recursive call
  while(current->getData() != data && current != NULL) {
    if(current != NULL) {
      if(current->getData() > data) {
	current = current->getLeft();
      }
      else {
        current = current->getRight();
      }
    }
    if(current == NULL) {
       break;
    }
  }
  if(current != NULL) {
    if(current->getData() == data) {
    cout << "The element is present in the list!" << endl;
  }
  }
  else {
    cout << "The element is not present in the list!" << endl;
  }
}
void fixTree(Node* root) {
 
}
void leftRotate(Node* & head, Node* target) {
  Node* swap = target->getRight();
  target->setRight(swap->getLeft());
  if(swap->getLeft() != NULL) {
    swap->getLeft()->setParent(target);
  }
  swap->getParent()->setParent(target->getParent());
  if(target->getParent() == NULL) {
    head = swap;
    
  }
  else {
    if(target = target->getParent()->getLeft()) {
      target->getParent()->setLeft(swap);
    }
    else {
      target->getParent()->setRight(swap);
    }
  }
  swap->setLeft(target);
  target->setParent(swap);
}
