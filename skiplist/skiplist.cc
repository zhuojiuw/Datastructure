#include "skiplist.h"
#include <cstdlib>
#include <iostream>

SkipList::SkipList(int level) {
    if(level>MAXLEVEL){
        delete(this);
    }
    head = new Node;
    end = new Node;
    head->nodelevel = level;
    end->nodelevel = level;
    for(int i = 0; i < head->nodelevel; i++) {
        head->next[i] = end;
    }
}

SkipList::~SkipList(){
    delete(head);
}

int SkipList::Search(int key) {
    Node * node1 = head;
    for(int i = node1->nodelevel - 1; i >= 0; i--) {
        while(true) {
            Node * node2 = node1->next[i];
            if(node2 == end || node2->key >key) {
                break;
            } else if (node2->key == key) {
                return node2->value;
            } else {
                node1 = node2;
            }
        }
    }
    return -1;
}

void SkipList::Insert(int key, int value) {
    Node * newnode = new Node;
    newnode->key = key;
    newnode->value = value;
    int level = newnode->nodelevel = Randomlevel();
    Node * node1 = head;
    for(int i = level - 1; i >= 0; i--) {
        while(true) {
            Node * node2 = node1->next[i];
            if(node2 == end || node2->key >key) {
                break;
            } else if (node2->key == key) {
                return;
            } else {
                node1 = node2;
            }
        }
        for(int i = 0; i < level; i++) {
            newnode->next[i] = node1->next[i];
            node1->next[i] = newnode;
        }
    }
}

void SkipList::Delete(int key) {
    Node * node1 = head;
    Node * update[level];
    Node * target;
    for(int i = node1->nodelevel - 1; i >= 0; i--) {
        while(true) {
            Node * node2 = node1->next[i];
            if(node2 == end || node2->key > key) {
                break;
            } else if(node2->key == key) {
                target = node2;
                update[i] = node1;
                break;
            } else {
                node1 = node2;
            }
        }
    }
    if(target != nullptr) {
        for(int i =node1->nodelevel - 1; i >= 0; i--) {
            if(update[i] != nullptr) {
                update[i]->next[i] = target->next[i];
            }
        }
    }
    delete(target);
}

int SkipList::Randomlevel() {
    int level = 1;
    while(level < level && rand()&1) level++;
    return level;
}
int main(){
    SkipList * skipList = new SkipList(6);
    skipList->Insert(1,2);
    skipList->Insert(2,3);
    std::cout<<skipList->Search(2);
    skipList->Delete(2);
    std::cout<<skipList->Search(2);
    return 0;
}