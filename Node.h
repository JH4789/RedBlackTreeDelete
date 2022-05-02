#ifndef NODEHEADER
#define NODEHEADER
#include <iostream>
using namespace std;
//Nothing to see here
class Node{
 public:
  Node(int newdata);
  void setData(int newdata);
  int getData();
  int getSLeft();
  int getSRight();
  
  ~Node();
  void printNode();
  void setLeft(Node*);
  void setRight(Node*);
  void setParent(Node*);
  Node* getUncle();
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  bool returnColor();
  void changeColor();
  void setColor(bool);
 private:
  int data;
  Node* left;
  Node* right;
  bool color;
  Node* parent;
};
#endif

