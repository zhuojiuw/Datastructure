// you should implement these method
#include "bplustree.h"
using namespace gearfactory;


void BplusTree::Insert(int key, int value){
  // step1. find the suitable position for this key 
  Node<1024, true> * node = Find(key);
  // step2. construct a Inner or Leaf Node to insert 
  node->insert(key, value);
}

void BplusTree::Delete(int key){
  // step1. find the key 
  Node<1024, true> * node = Find(key);
  // step2. remove the node which contains the key
  node->remove(key);
}

Node<1024, true> * BplusTree::Find(int key){
  // step1. find the leaf Node for this key 
  Node<1024> * node = root_;
  while(!node->is_leaf) {
    node = node->child[node->binary_search];
  }
  return (Node<1024, true>*)node;
}

std::vector<std::pair<int,int>> BplusTree::Scan(int start, int end){
  // step1. find the start LeafNode and the end LeafNode 
  Node<1024, true> * nodeStart = Find(start);
  Node<1024, true> * nodeEnd = Find(end);
  int positionStart = nodeStart->binary_search(start);
  int positionEnd = nodeEnd->binary_search(end);
  // step2. move the pointer to the vector 
  std::vector<std::pair<int,int>> vec;
  Node<1024, true> * node = nodeStart;
  while(node != nodeEnd) {
    auto vec1 = node->scan(start, end);
    vec.insert(vec.end(), vec1.begin(), vec1.end());
  }
  return vec;
}