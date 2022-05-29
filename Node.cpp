#include "Node.h"
//Standard node construction, copied from previous projects
//Added a checkRed function to check for nodes with black/null children
Node::Node(int newdata) {
  data = newdata;
  left = NULL;
  right = NULL;
  color = true;
  parent = NULL;
}
Node::~Node() {
  left = NULL;
  right = NULL;
}
bool Node::returnColor() {
  return color;
}
void Node::changeColor() {
  if(color == true) {
    color = false;
  }
  else {
    color = true;
  }
}
bool Node::checkRed() {
  bool redpresent = false;
  if(left != NULL) {
    if(left->returnColor() == true) {
      redpresent = true;
    }
  }
  if(right != NULL) {
    if(right->returnColor() == true) {
      redpresent = true;
    }
  }
  return redpresent;
}
void Node::setColor(bool newcolor) {
  color = newcolor;
}
void Node::printNode() {
  cout << data;
  if(color == true) {
    cout << "R";
  }
  else {
    cout << "B";
  }
  if(parent != NULL) {
    cout << parent->getData();
  }
}
Node* Node::getUncle() {
  Node* uncle = NULL;
  
  if(parent->getParent() == NULL) {
    uncle = NULL;
  }
  else if(parent->getParent()->getLeft() == parent) {
    uncle = parent->getParent()->getRight();
  }
  else {
    uncle = parent->getParent()->getLeft();
  }
  
  return uncle;
}
Node* Node::getParent() {
  return parent;
}
void Node::setParent(Node* parentnode) {
  parent = parentnode;
}
void Node::setData(int newdata) {
  data = newdata;
}
int Node::getData() {
  return data;
}
void Node::setLeft(Node* newleft) {
  left = newleft;
}
void Node::setRight(Node* newright) {
  right = newright;
}
Node* Node::getLeft() {
  return left;
}
Node* Node::getRight() {
  return right;
}
