//
// Created by zhang on 15/01/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "intervalTree.h"

Node* newNode(Interval i)
{
    Node* temp = malloc(sizeof(Node));
    temp->interval = i;
    temp->maxValue = i.high;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}


Node* insert(Node* root, Interval i)
{
    if (root == NULL)
    {
        return newNode(i);
    }
    int l = root->interval.low;
    if (i.low < l)
    {
        root->left = insert(root->left, i);
    }
    else
    {
        root->right = insert(root->right, i);
    }
    // update maxValue
    if (root->maxValue < i.high)
    {
        root->maxValue = i.high;
    }
    return root;

}

_Bool overlapInterval(Interval i1, Interval i2)
{
    return (i1.low < i2.high && i2.low < i1.high);
}

void inOrder(Node* root)
{
    if (root == NULL) return;
    inOrder(root->left);
    printf("[ %d, %d ] max = %d\n", root->interval.low, root->interval.high, root->maxValue);
    inOrder(root->right);
}

_Bool overlap(Interval i, Node* root)
{
    if (root == NULL) return 0;
    _Bool flagLeft = overlap(i, root->left);
    if (overlapInterval(i, root->interval))
    {
        return 1;
    }
    _Bool flagRight = overlap(i, root->right);
    return flagLeft || flagRight;
}

void testTree()
{

    printf("Begin test tree\n");
    Interval ints[] = {{1, 3}, {7, 9}, {11, 13}};
    int n = sizeof(ints)/sizeof(ints[0]);
    //Interval** intervals = malloc(15 * sizeof(Interval*));
    Node *root = NULL;

    Interval in;
    for (int i = 0; i < n; i++)
    {
        in = (Interval){ints[i].low, ints[i].high};
        root = insert(root, in);
    }

    inOrder(root);
    Interval temp = {3, 4};
    printf("%d", overlap(temp, root));
}

void delTree(Node* root)
{
    //à compléter
}

