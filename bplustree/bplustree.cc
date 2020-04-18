// you should implement these method
#include "bplustree.h"
using namespace gearfactory;

void BplusTree::Insert(int key, int value){
  // step1. find the suitable position for this key 

  // step2. construct a Inner or Leaf Node to insert 
}

void BplusTree::Delete(int key){
  // step1. find the key 

  // step2. remove the node which contains the key
}

Node<1024, true> * BplusTree::Find(int key){
  // step1. find the leaf Node for this key 
}

std::vector<Node<1024, true> *> BplusTree::Scan(int start, int end){
  // step1. find the start LeafNode and the end LeafNode 

  // step2. move the pointer to the vector 
}