//
// Created by zhang on 15/01/17.
//


#ifndef ORDO_INTERVALTREE_H
#define ORDO_INTERVALTREE_H

typedef struct Node Node;
typedef struct Interval Interval;
struct Interval {
    int low;
    int high;
};


struct Node{
    Interval interval;
    int maxValue;
    Node* left;
    Node* right;
};

Node* newNode(Interval i);
_Bool overlapInterval(Interval i1, Interval i2);
_Bool overlap(Interval i, Node*);
Node* insert(Node* root, Interval i);
void inOrder(Node* root);
void delTree(Node* root);
void testTree();




#endif //ORDO_INTERVALTREE_H
