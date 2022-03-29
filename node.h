//
// Created by usrname on 17.03.2022.
//

#ifndef LAB23_NODE_H
#define LAB23_NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _node{
    int key;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} node;

int max(int a,int b);
void initialization(node *n);
void free_node(node *n);
node *create_node(int val);
void insert(node *bt,node *n);
void print_nodes(node *n, int k);
void inorderprint_nodes(node *n);
void preorderprint_node(node *n);
void postorderprint_node(node *n);
node *minimum(node *n);
node *maximum(node *n);
node *search(node *n,int val);
node *prev(node *bt,node *n);
node *next(node *bt,node *n);
node *delete(node *bt,int k);
void destruction(node *n);
int depth_difference(node *n);
bool BTree_check(node *n);
int deepest_leaf_value(node *n);
int vertex_number(node *n);
int non_terminal_number(node *n);
int max_depth(node *n);
#endif //LAB23_NODE_H
