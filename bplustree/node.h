#ifndef __GF_BPLUSTREE_NODE__
#define __GF_BPLUSTREE_NODE__

namespace gearfactory{
  // The inner node in the BplusTree to contain the data and key 
  template<int level, bool leaf = false>
  class Node{
    public: 
      int key;
      int value;
      int index[level];

      Node<level> * next;
      Node<level> * child;
      Node<level> * parent;
      Node<level> * last;

      // indicate this node is a leaf node 
      bool is_leaf(){return leaf;};

      // clean up the child node 
      ~Node(){
        delete child;
      }

      // split this node to two node 
      void split(){
        // you should complete this method of Node 
      }

      // merge this node with the sibiling
      void merge(Node<level, leaf> * sibiling){
        // you should complete this method of Node 
      }
  };
} // namespace gearfactory


#endif // !__GF_BPLUSTREE_NODE__