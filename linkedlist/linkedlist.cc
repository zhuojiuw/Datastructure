#include "linkedlist.h"
#include <iostream>

LinkedList::LinkedList() {
    Node * beginNode = new Node();
    Node * endNode = new Node();
    beginNode->next = beginNode->pre = endNode;
    endNode->next = endNode->pre = beginNode;
    root_ = beginNode;
}
LinkedList::~LinkedList() {
    Node * node = root_->next;
    while(node != root_) {
        Node * now = node->next;
        delete(node);
        node = now;
    }
    delete root_;
}
void LinkedList::Insert(int key, int value) {
    Node * nownode = root_->next;
    while(nownode->next != root_) {
        if(nownode->key >= key) {
            break;
        }
        nownode = nownode->next;
    }
    Node * node = new Node;
    node->key = key;
    node->value = value;
    node->pre = nownode->pre;
    node->next = nownode;
    nownode->pre->next = node;
    nownode->pre = node;
}

void LinkedList::Delete(int key) {
    Node * node = root_;
    node = root_->next;
    while(node->next != root_) {
        if(node->key == key) {
            node->pre->next = node->next;
            node->next->pre = node->pre;
            delete(node);
            break;
        }
        node = node->pre;
    }
}

void LinkedList::update(int key, int newValue) {
    Delete(key);
    Insert(key, newValue);
}

int LinkedList::Find(int key) {
    Node * node = root_->next;
    while(node->next != root_) {
        if(node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}
int main(){
    LinkedList * list = new LinkedList;
    list->Insert(2,2);
    list->Insert(1,1);
    std::cout<<list->Find(2);
    //list->Insert(3,3);
    //list->Insert(4,4);
    //std::cout << list->Find(1);
}