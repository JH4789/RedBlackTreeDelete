/*
Name: Jayden Huang
Date: 5/8/2022
Project: Red-Black Tree insertion, implementation of red black tree that supports insert and search
*/
#include <iostream>
#include "Node.h"
#include <cstring>
#include <math.h>
#include <fstream>
void printFormat(Node* head, int space);
void addTree(Node* & head, Node* current, Node* newnode);
void searchTree(Node* current, int data);
void fixTree(Node* & head, Node* current);
void fixTreeDelete(Node* & head, Node* sibling);
void leftRotate(Node* & head, Node* target);
void rightRotate(Node* & head, Node* target);
void deleteTree(Node* & head, Node* current, int data);
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
      cout << "Enter the number you would like to search for: " << endl;
      cin >> input;
      searchTree(treehead, input);
    }
    else if (strcmp(commandinput, "DELETE") == 0) {
       cout << "Enter the number you would like to delete: " << endl;
       cin >> input;
       deleteTree(treehead, treehead, input);
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
    
    if(current->getUncle() != NULL && current->getUncle()->returnColor() == true) {
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
        //All cases are done according to algorithm
      	//LL case
        if(grandparent->getLeft() == current->getParent() && current == current->getParent()->getLeft()) {
	  cout << "LL";
	  rightRotate(head, grandparent);
	  Node* sibling = current->getParent()->getRight();
          bool siblingcolor = true;
	  if(sibling != NULL) {
	    siblingcolor = sibling->returnColor();
	  }
	  else {
            siblingcolor = false;
	  }
          sibling->setColor(current->getParent()->returnColor());
	  current->getParent()->setColor(siblingcolor);	  
	}
	//LR
	else if(grandparent->getLeft() == current->getParent() && current == current->getParent()->getRight()) {
          cout << "LR" << endl;
	  leftRotate(head, current->getParent());
	  
	  rightRotate(head, current->getParent());
          current->printNode();
	  bool color = current->returnColor();
	  current->setColor(current->getRight()->returnColor());
	  current->getRight()->setColor(color);
	}
	//RR
	else if(grandparent->getRight() == current->getParent() && current == current->getParent()->getRight()) {
          cout << "RR";
	  leftRotate(head, grandparent);
	  Node* sibling = current->getParent()->getLeft();
	  bool siblingcolor = true;
	  if(sibling != NULL) {
	    siblingcolor = sibling->returnColor();
	  }
	  else {
            siblingcolor = false;
	  }
          sibling->setColor(current->getParent()->returnColor());
	  current->getParent()->setColor(siblingcolor);	  
        }
	//RL
	else if(grandparent->getRight() == current->getParent() && current == current->getParent()->getLeft()) {
          cout << "RL" << endl;
	  rightRotate(head, current->getParent());	  
	  leftRotate(head, current->getParent());
          bool color = current->returnColor();	  
	  current->setColor(current->getLeft()->returnColor());
	  current->getLeft()->setColor(color);
	
	}
      }
    }
}
//Rotate functions
void leftRotate(Node* & head, Node* target) {
  //Swaps subtrees special case for head
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
    if(target->getRight() != NULL) {
    subtree = target->getRight()->getLeft();
    }
    Node* targetright = target->getRight();
    if(target->getParent()->getLeft() == target) {
    target->getParent()->setLeft(targetright);
    targetright->setParent(target->getParent());
    }
    else {
      target->getParent()->setRight(targetright);
      targetright->setParent(target->getParent());
    }
    targetright->setLeft(target);
    targetright->setParent(target->getParent());
    target->setParent(targetright);
    target->setRight(subtree);    
    if(subtree != NULL) {
      subtree->setParent(target);
    }
  }
}
void rightRotate(Node* & head, Node* target) {
  //See left rotate
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
      targetleft->setParent(target->getParent());
      target->setParent(targetleft);
      target->setLeft(subtree);
      if(subtree != NULL) {
	subtree->setParent(target);
      }
    
  }  
}
void deleteTree(Node* & head, Node* current, int data) {
  //Could use a bit more recursion on the two child case
  if(head == NULL) {
    cout << "The tree is empty!" << endl;
  }
  //Checks for three cases: one child, two children, no children
  //Parent is needed because just calling the destructor was not working
  if(current != NULL) {
    if(current->getData() == data) {
      //No children case
      if(current->getLeft() == NULL && current->getRight() == NULL) {
	if(current == head) {
          delete head;
	  head = NULL;
	}
        else if(current->getParent()->getLeft() == current) {
	  current->getParent()->setLeft(NULL);
	  Node* sibling = current->getParent()->getRight();
	  fixTreeDelete(head, sibling);
	  delete current;
	}
	else {
          current->getParent()->setRight(NULL);
	  Node* sibling = current->getParent()->getLeft();
	  fixTreeDelete(head, sibling);
	  delete current;
	}
      }
      //Only right child present case
      else if(current->getLeft() == NULL) {
	if(current == head) {
	  Node* temp = head;
	  head = head->getRight();
	  delete temp;
	}
	else if(current->getParent()->getLeft() == current) {
          Node* temp = current;
	  current->getParent()->setLeft(current->getRight());
	  current->getLeft()->setParent(current->getParent());
	  delete temp;
	}
	else {
          Node* temp = current;
	  bool currentcolor = current->returnColor();
	  current->getRight()->setColor(currentcolor);
	  current->getParent()->setRight(current->getRight());
	  current->getRight()->setParent(current->getParent());
	  delete temp;
	}
      }
      //Only left child present case
      else if(current->getRight() == NULL) {
        
	if(current == head) {
	  Node* temp = head;
	  head = head->getLeft();
	  delete temp;  
	}
        
	else if(current->getParent()->getLeft() == current) {
          Node* temp = current;
	  //FIGURE THIS STUFF OUT PLZ
	  if(current->returnColor() == true || current->getLeft()->returnColor() == true) {
            current->getLeft()->setColor(false);
	    current->getParent()->setLeft(current->getLeft());
	     current->getLeft()->setParent(current->getParent());
	  }
	  else {
	    cout << "FLAG";
	    current->getParent()->setLeft(current->getLeft());
	    current->getLeft()->setParent(current->getParent());
	    Node* sibling = current->getParent()->getRight(); 
	    fixTreeDelete(head, sibling);
	  }
	  delete temp;
	}
	else {
          Node* temp = current;
	  if(current->returnColor() == true || current->getLeft()->returnColor() == true) {
            current->getLeft()->setColor(false);
	    current->getParent()->setRight(current->getLeft());
	     current->getLeft()->setParent(current->getParent());
             
	  }
	  
	  else {
	    cout << "FLAG";
	    current->getParent()->setRight(current->getLeft());
	    current->getLeft()->setParent(current->getParent());
	    Node* sibling = current->getParent()->getRight();
	    
	    fixTreeDelete(head, sibling);
	  }
	    delete temp;  
	}
	
      }
      //Two children case
      else {
	//Swaps the current node and its inorder successor
	Node* inorder = current->getRight();
	Node* orderparent = current;
	while(inorder->getLeft() != NULL) {
          orderparent = inorder;
	  inorder = inorder->getLeft();
	}
	int newdata = inorder->getData();
	int deletedata = current->getData();
	inorder->setData(current->getData());
	current->setData(newdata);
	//This should be a recursive call but it wasn't working so I just copied the code
	if(inorder->getLeft() == NULL && inorder->getRight() == NULL) {
          if(orderparent->getLeft() == inorder) {
	    orderparent->setLeft(NULL);
	  }
	  else {
            orderparent->setRight(NULL);
	  }
	  Node* temp = inorder;
	  delete temp;
	}
	else if(inorder->getRight() == NULL) {
          Node* temp = inorder;
	  
	  orderparent->setLeft(inorder->getLeft());
	  delete temp;
	}
	else {
	  Node* temp = inorder;
	  orderparent->setRight(inorder->getRight());
	  delete temp;
	}
      }
    }
    //Same as in print, navigates through the tree
    else if(current->getData() > data) {
      
      deleteTree(head, current->getLeft(), data);
    }
    else {
      
      deleteTree(head, current->getRight(), data);
    }
  }
}
void fixTreeDelete(Node* & head, Node* sibling) {
  if(sibling == NULL) {
    cout << "NULL!" << endl;
    return;
  }
  else if(sibling->returnColor() == false) {
    
    //Sibling is left child
    if(sibling->getParent()->getLeft() == sibling) {
      cout << "LEFT" << endl;
      if(sibling->getLeft() == NULL && sibling->getRight() == NULL) {
	cout << "FLAG, BOTH CHILDREN NULL" << endl;
	sibling->changeColor();
      }
      //THIS IS WORKING FIX LR
      else if(sibling->getLeft() != NULL) {
        //LL
	if(sibling->getLeft()->returnColor() == true) {
          cout << "DLL" << endl;
	  bool parentcolor = sibling->getParent()->returnColor();
	  sibling->getParent()->setColor(sibling->returnColor());
	  sibling->setColor(parentcolor);
	  rightRotate(head, sibling->getParent());
	  sibling->getLeft()->setColor(false);
	}
      }
	//LR
       else {
	 if(sibling->getRight()->returnColor() == true) {
	   cout << "DLR" << endl;
	   bool siblingcolor = sibling->returnColor();
	   sibling->setColor(sibling->getRight()->returnColor());
	   sibling->getRight()->setColor(siblingcolor);
           leftRotate(head, sibling);
	   sibling = sibling->getParent();

	   //Below is same as LL case
	   sibling->printNode();
	   sibling->getParent()->printNode();
	   bool parentcolor = sibling->getParent()->returnColor();
	   sibling->getParent()->setColor(sibling->returnColor());
	   sibling->setColor(parentcolor);
	   rightRotate(head, sibling->getParent());
	   sibling->getLeft()->setColor(false);
	   }
       }
    
    }
    //Sibling is right child
    else {
      
      if(sibling->getRight() == NULL && sibling->getLeft() == NULL) {
        cout << "BOTH CHILDREN NULL" << endl;
      }
      else if(sibling->getRight()->returnColor() == true) {
         cout << "DRR" << endl;
	  bool parentcolor = sibling->getParent()->returnColor();
	  sibling->getParent()->setColor(sibling->returnColor());
	  sibling->setColor(parentcolor);
	  leftRotate(head, sibling->getParent());
	  sibling->getRight()->setColor(false);
      }
      else {
        cout << "DRL" << endl;
	/*
        bool siblingcolor = sibling->returnColor();
	sibling->setColor(sibling->getLeft()->returnColor());
	sibling->getLeft()->setColor(siblingcolor);
        rightRotate(head, sibling);
	sibling = sibling->getParent();

	//Below is same as LL case
	sibling->printNode();
	sibling->getParent()->printNode();
	bool parentcolor = sibling->getParent()->returnColor();
	sibling->getParent()->setColor(sibling->returnColor());
	sibling->setColor(parentcolor);
	leftRotate(head, sibling->getParent());
	sibling->getRight()->setColor(false);
	*/ 
      }
    }
  }
}
