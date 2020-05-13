#ifndef __GF_BPLUSTREE_NODE__
#define __GF_BPLUSTREE_NODE__

namespace gearfactory{
  // The inner node in the BplusTree to contain the data and key 
  template<int level, bool leaf = false>
  class Node{
    public: 
      int key[level];
      int value[level];
      int num = 0;

      Node<level> * child[level+1];
      Node<level> * pre;
      Node<level> * next;
      Node<level> * parent;

      // indicate this node is a leaf node 
      bool is_leaf() { return leaf; };

      // clean up the child node 
      ~Node(){
        delete child[level];
      }

      // search a key from Node
      int binary_search(int key) {
        // find the child noed
        int l = 1, r = num;
        if (key < this.key[l]) return 1;
        if (this.key[r - 1] <= key) return r;
        while (l < r - 1) {
          int mid = (l + r) >> 1;
          if (this.key[mid] > key)
            r = mid;
          else
            l = mid;
        }
        return l + 1;
      }

      // insert key/value to leaf Node
      void insert(int key, int value) {
        int idx = binary_search(key);
        idx--;
        for(int i = num; i > idx; i--) {
          this.key[i] = this.key[i-1];
          this.value[i] = this.value[i-1];
        }
        if (idx == 0) {
          parent->remove(this.key[1]);
          parent->insert(key, value, this);
        }
        this.key[idx] = key;
        this.value[idx] = value;
        num++;
        if(num == level) {
          split();
        }
      } 

      //remove a key from Node
      void remove(int key) {
        int idx = binary_search(key);
        idx--;
        int keynum = this.key[idx];
        for(int i = idx; i < num - 1; i++) {
          this.key[i] = this.key[i+1];
          this.value[i] = this.value[i+1];
          this.child[i] = this.child[i+1];
        }
        num--;
        if(this.parent == nullptr) {
          if(num == 1) {
            Node<level> * node = this;
            this = this.child[0];
            free(node);
          }
        } else if(num < level / 2) {
          if(this.pre != nullptr && this.pre->num > level / 2) {
            int prekey = this.pre->key[this.pre->num-1];
            int prevalue = this.pre->value[this.pre->num-1];
            int prechild = this.pre->child[this.pre->num-1];
            insert(prekey, prevalue, prechild);
            this.pre->remove(prekey);
          } else if(this.next != nullptr && this.next->num >level / 2) {
            int nextkey = this.next->key[0];
            int nextvalue = this.next->value[0];
            int nextchild = this.next->child[0];
            insert(nextkey, nextvalue, nextchild);
            this.next.remove(nextkey);
          } else if(this.pre != nullptr) {
            merge(this.pre);
          } else {
            merge(this.next);
          }
        }
        if(idx == 0) {
          this.parent->remove(keynum);
          this.parent->insert(this.key[0], this.value[0], this);
        } else {
          this.parent->remove(keynum);
        }
      }

      // return some key/value
      std::vector<std::pair<int, int>> scan(int start, int end) {
        // scan the key/value from Node
        std::vector<std::pair<int, int>> vec;
        for(int i = 0; i < num; i++) {
          if(this.key[i]>=start && this.key[i] <= end) {
            vec.insert(std::make_pair(this.key[i], this.value[i]));
          }
        }
        return vec;
      }

    private:

       // true or false a key exists
      bool find(int key) {
        for(int i = 0; i < num; i++) {
          if(this.key[i] == key) {
            return true;
          }
        }
        return false;
      }

      // insert key/value and pointer to inner Node
      void insert(int key, int value, Node<1024> * pointer) {
        int idx = binary_search(key);
        idx--;
        for(int i = num; i > idx; i--) {
          this.key[i] = this.key[i-1];
          this.value[i] = this.value[i-1];
          this.child[i] = this.child[i-1];
        }
        if (idx == 0) {
          parent->remove(this.key[1]);
          parent->insert(key, value, this);
        }
        this.key[idx] = key;
        this.value[idx] = value;
        this.child[idx] = pointer;
        num++;
        if(num == level) {
          split();
        }
      }

      // split this node to two node 
      void split(){
        // you should complete this method of Node 
        int mid = num / 2;
        if(parent) {
          // node is not root
          Node<level, leaf> * node = new Node<level, leaf>();
          node->pre = this;
          node->next = this.next;
          node->parent = this.parent;
          this.next = node;
          for(int i = mid; i < num; i++) {
            node->key[i-mid] = this.key[i];
            node->value[i-mid] = this.value[i]; 
          }
          num = mid;
          parent.insert(node->key[0], node->value[0], node);
        } else {
          // is root
          // we cant change who the root is, 
          // so we need to update root
          Node<level, leaf> * nodeleft = new Node<level, false>();
          Node<level, leaf> * node = new Node<level, false>();
          for(int i = 0; i < mid; i++) {
            nodeleft->key[i] = this.key[i];
            nodeleft->value[i] = this.value[i];
            nodeleft->child[i] = this.child[i];
          }
          nodeleft->parent = this;
          nodeleft->num = mid;
          nodeleft->next = node;
          for(int i = mid; i < num; i++) {
            node->key[i-mid] = this.key[i];
            node->value[i-mid] = this.value[i];
            node->child[i] = this.child[i];
          }
          node->parent = this;
          node->num = num - mid;
          node->pre = nodeleft;
          num = 0;
          leaf = false;
          insert(nodeleft->key[0], nodeleft->value[0], nodeleft);
          insert(node->key[0], node->value[0], node);
        }
      }

      // merge this node with the sibiling
      void merge(Node<level, leaf> * sibiling){
        // you should complete this method of Node 
        if(sibiling->key[0] < this.key[0]) {
          this.pre = sibiling->pre;
          sibiling->pre->next = this;
        } else {
          this.next = sibiling->next;
          sibiling->next->pre = this;
        }
        for(int i = 0; i < sibiling->num; i++) {
          this.insert(sibiling->key[i], sibiling->value[i], sibiling->child[i]);
          sibiling->parent.remove(sibiling->key[0]);
          free(sibiling);
        }
      }
  };
} // namespace gearfactory


#endif // !__GF_BPLUSTREE_NODE__