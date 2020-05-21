#ifndef __SEGMENT_TREE_H__
#define __SEGMENT_TREE_H__

class Node;

class SegmentTree{
    public:
        SegmentTree(int * array, int length);

        ~SegmentTree();

        int search(int l, int r) {
            return search(root_, l, r);
        }

        //Single point modification
        void revise(int dis, int newdata){
            revise(root_, dis, newdata);
        }

        //Interval modification
        void revise(int l, int r, int add) {
            revise(root_, l, r, add);
        }


    private:
        Node * root_;
        
        void build(Node * p, int *array, int l, int r);

        int search(Node * p, int l, int r);

        void revise(Node * p, int dis, int newdata);

        void revise(Node * p, int l, int r, int add);
};

class Node{
    public:
        Node * left;
        Node * right;
        int l,r;
        int sum;
        int lazy;
        Node() {
        } 
        ~Node(){
            if(left) delete left;
            if(right) delete right;
        }

};

#endif // !__SEGMENT_TREE_H__