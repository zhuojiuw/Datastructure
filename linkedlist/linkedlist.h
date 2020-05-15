#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

class LinkedList{
    public:
        LinkedList() {
            Node * beginNode = new Node;
            Node * endNode = new Node;
            root_ = beginNode;

        }
        ~LinkedList() {
            Node * node = root_->next;
            while(node != root_) {
                Node * now = node->next;
                delete(node);
                node = now;
            }
            delete root_;
        }
        void Insert(int key, int value) {
        }

        void Delete(int key) {
        }

        void update(int key, int newValue) {
        }

        int Find(int key) {
        }
    private:
        Node * root_;
};

class Node{
    public:
        int key;
        int value;
        Node * pre;
        Node * next;
        ~Node(){
        }
};

#endif // !__LINKED_LIST_H__