#include <iostream>
#include "Node.h"
#include <cstring>
#include <math.h>
#include <fstream>
void printFormat(Node* head, int space);
void addTree(Node* & head, Node* current, Node* newnode);
void searchTree(Node* current, int data);
void fixTree(Node* & head, Node* current);
void leftRotate(Node* & head, Node* target);
void rightRotate(Node* & head, Node* target);
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
      
      printFormat(treehead, 3);
    }
    else if (strcmp(commandinput, "SEARCH") == 0) {

      //leftRotate(treehead, treehead);
      Node* newnode = new Node(4);
      treehead->setLeft(newnode);
      newnode->setParent(treehead);
      Node* rightnode = new Node(10);
      rightnode->changeColor();
      rightnode->setParent(treehead);
      treehead->setRight(rightnode);
      
      //leftRotate(treehead, treehead->getLeft());
      //rightRotate(treehead, treehead->getLeft());
      
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
	newnode->setParent(current);
	fixTree(head, newnode);
	return;
      }
      else {
        addTree(head, current->getRight(), newnode);
      }
    }
    else if(newnode->getData() < current->getData()) {
    if(current->getLeft() == NULL) {
      current->setLeft(newnode);
      newnode->setParent(current);
      fixTree(head, newnode);
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
	   fixTree(head, newnode);
           return;
       }
       else if(current->getRight() == NULL) {
           current->setRight(newnode);
	   newnode->setParent(current);
	   fixTree(head, newnode);
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
void fixTree(Node* &head, Node* current) {
  Node* grandparent = current->getParent()->getParent();
  if(current->getParent()->returnColor() == true) {
    if(current->getUncle() == NULL) {
      cout << "NULL" << endl;
      if(current->getParent()->getLeft() == current) {
        
	if(grandparent == head) {
	rightRotate(head, current->getParent()->getParent());
	current->printNode();
        
	head->changeColor();
	head->getRight()->changeColor();
	}
	else {
        rightRotate(head, current->getParent()->getParent());
	current->printNode();
	grandparent->changeColor();
	grandparent->getRight()->changeColor();
	}
      }
      else {
        leftRotate(head, current->getParent()->getParent());
	current->printNode();
	head->changeColor();
	head->getLeft()->changeColor();
      }
    }
    else {
      cout << "UNCLE PRESENT" << endl;
      if(current->getUncle()->returnColor() == true) {
	current->getUncle()->setColor(false);
	current->getParent()->setColor(false);
        if(grandparent != head) {
	grandparent->setColor(true);
	}
	else {
	  grandparent->setColor(false);
	}
      }
      else {
	//LL case
        if(grandparent->getLeft() == current->getParent() && current == current->getParent()->getLeft()) {
	  cout << "LL";
	  rightRotate(head, grandparent);
	  Node* sibling = current->getParent()->getRight();
	  bool siblingcolor = sibling->returnColor();
          sibling->setColor(current->getParent()->returnColor());
	  current->getParent()->setColor(siblingcolor);
	  
	}
	else {
          cout << "OTB";
	}
      }
    }
  }
}
void leftRotate(Node* & head, Node* target) {
  Node* subtree = NULL;
  if(target == head) {
    subtree = target->getRight()->getLeft();
    head = target->getRight();
    head->setLeft(target);
    head->setParent(NULL);
    target->setParent(head);
    target->setRight(subtree);
    if(subtree != NULL) {
    subtree->setParent(target);
    }
  }
  
  else {
    
      
    subtree = target->getRight()->getLeft();
    Node* targetright = target->getRight();
    if(target->getParent()->getLeft() == target) {
    target->getParent()->setLeft(targetright);
    }
    else {
      target->getParent()->setRight(targetright);
    }
    targetright->setLeft(target);
    target->setRight(subtree);    
    
  }
}
void rightRotate(Node* & head, Node* target) {
  
  Node* subtree = NULL;
  if(target == head) {
    subtree = target->getLeft()->getRight();
    head = target->getLeft();
    head->setRight(target);
    head->setParent(NULL);
    target->setLeft(subtree);
    target->setParent(head);
    if(subtree != NULL) {
      subtree->setParent(target);
    }
  }
  else {
    if(target->getLeft() == NULL) {
      cout << "UH OH";
    }
    else {
      subtree = target->getLeft()->getRight();
      Node* targetleft = target->getLeft();
      cout << target->getData() << endl;
      if(target->getParent()->getLeft() == target) {
      target->getParent()->setLeft(targetleft);
      targetleft->setParent(target->getParent());
      }
      else {
	target->getParent()->setRight(targetleft);
	target->setParent(target->getParent());
      }
      targetleft->setRight(target);
      target->setParent(targetleft);
      target->setLeft(subtree);
      if(subtree != NULL) {
	subtree->setParent(target);
      }
    }
  }
  
}
