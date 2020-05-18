#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

const int MAXLEVEL = 32;
class Node;
class SkipList{
    public:
        int level;
        Node * head;
        Node * end;

        SkipList(int level);
        
        ~SkipList();

        Node* Find(int key);

        int Search(int key);

        void Insert(int key, int value);

        void Delete(int key);
        
        int Randomlevel();


};

class Node{
    public:
        int key;
        int value;
        Node * next[MAXLEVEL];
        int nodelevel;
        Node(){
        }
        ~Node(){
            if(next[0] != nullptr){
                delete(next[0]);
            }
        }
};

#endif // !__SKIPLIST_H__