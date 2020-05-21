#include <iostream>
#include "segmenttree.h"

SegmentTree::SegmentTree(int * array, int length) {
    root_ = new Node;
    build(root_, array, 0, length - 1);
}

SegmentTree::~SegmentTree() {
    if(root_)
        delete(root_);
}

int SegmentTree::search(Node * p, int l, int r) {
    if(l <= p->l && r >= p->r) {
        return p->sum;
    }
    int mid = (p->l + p->r) >> 1;
    if(p->lazy) {
        p->left->sum += p->lazy * (mid - p->l + 1);
        p->right += p->lazy * (p->r - mid);
        p->left->lazy += p->lazy;
        p->right->lazy +=p->lazy;
        p->lazy = 0;
    }
    int sum = 0;
    if(l <= mid) {
        sum += search(p->left, l, r);
    }
    if(r > mid) {
        sum += search(p->right, l, r);
    }
    return sum;
}

void SegmentTree::revise(Node * p, int dis, int newdata){
    revise(p, dis, dis, newdata);
}

void SegmentTree::revise(Node * p, int l, int r, int add) {
    if(p->l >= l && p->r <= r) {
        p->sum += add * (r-l+1);
        p->lazy += add;
        return ;
    }
    int mid = (p->l + p->r) >> 1;
    if(p->lazy) {
        p->left->sum += p->lazy * (mid - p->l + 1);
        p->right->sum += p->lazy * (p->r - mid);
        p->left->lazy += p->lazy;
        p->right->lazy += p->lazy;
        p->lazy = 0;
    }
    if(l <= mid) {
        revise(p->left, l, r, add);
    }
    if(r > mid) {
        revise(p->right, l, r, add);
    }
    p->sum = p->left->sum + p->right->sum;
}

void SegmentTree::build(Node * p, int *array, int l, int r) {
    p->l = l, p->r = r;
    if(l == r) {
        p->sum = array[l];
        return ;
    }
    Node * leftnode = new Node;
    Node * rightnode = new Node;
    p->left = leftnode;
    p->right = rightnode;
    int mid = (l + r) >> 1;
    build(leftnode, array, l, mid);
    build(rightnode, array, mid+1, r);
    p->sum = leftnode->sum + rightnode->sum;
}
int main(){
    int a[15] = {1,2,3,4,5,6,7,8,9,10};
    SegmentTree sgt = SegmentTree(a, 10);
    std::cout<<sgt.search(0,8);
    sgt.revise(5,7,1);
    std::cout<<sgt.search(0,8);
    return 0;
}