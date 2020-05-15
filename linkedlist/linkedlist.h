#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

class Node;
class LinkedList{
    public:
        LinkedList();

        ~LinkedList();

        void Insert(int key, int value);

        void Delete(int key);

        void update(int key, int newValue);

        int Find(int key);
    private:
        Node * root_;
};

class Node{
    public:
        int key;
        int value;
        Node * pre;
        Node * next;
};

#endif // !__LINKED_LIST_H__