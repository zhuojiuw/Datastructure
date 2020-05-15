#include "linkedlist.h"

void LinkedList::Insert(int key, int value) {
    Node * node = root_;
    node->key = key;
    node->value = value;
    node->pre = root_;
    node->next = root_->next;
    root_->next->pre = node;
    root_->next = node;
}

void LinkedList::Delete(int key) {
    Node * node = root_;
    node = root_->next;
    while(node->pre != root_) {
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
    Node * node = root_;
    node = root_->next;
    while(node->pre != root_) {
        if(node->key == key) {
            return node->value;
            break;
        }
        node = node->pre;
    }
}