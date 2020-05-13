#ifndef __GF_BPLUSTREE__
#define __GF_BPLUSTREE__

#include <vector>
#include <utility>
#include "node.h"
#include <iostream>

namespace gearfactory{
  
  class BplusTree{
    public:

      BplusTree(): root_(nullptr){}

      void Insert(int key, int value);

      void Delete(int key);

      Node<1024,true> * Find(int key);

      std::vector<std::pair<int, int>> Scan(int start, int end);

      ~BplusTree(){
        if (root_ != nullptr) {
          delete root_;
        }
      }

    private:
      // This method will create a new inner node with level 1024
      inline Node<1024> * newInnweNode(int key, int value){
        Node<1024> * node = new Node<1024>();
        Node<1024> * child = new Node<1024>[1024 +1];
        node -> key[0] = key;
        node -> value[0] = value;
        node -> child[0] = child;
        return node;
      }

      // This method will create a new leaf node with level 1024
      inline Node<1024, true> * newLeafNode(int key, int value){
        Node<1024, true> * node = new Node<1024, true>();
        node -> key[0] = key;
        node -> value[0] = value;
        return node;
      }

    private:
      Node<1024> * root_;
  };
} // namespace gearfactory

#endif // !__GF_BPLUSTREE__