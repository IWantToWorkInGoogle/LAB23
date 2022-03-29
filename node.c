//
// Created by usrname on 17.03.2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


int max(int a,int b) {
    return (a > b) ? a : b;
}

typedef struct _node{
    int key;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} node;

void free_node(node *n) {
    n->key = 0;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    free(n);
    n = NULL;
}

node *create_node(int val) {
    node *n = (node *)malloc(sizeof(node));
    n->key = val;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(node *bt,node *n) {
    if(bt->key >= n->key) {
        if(bt->left == NULL) {
            bt->left = n;
            n->parent = bt;
        }
        else insert(bt->left,n);
    }
    else {
        if(bt->right == NULL) {
            bt->right = n;
            n->parent = bt;
        }
        else insert(bt->right,n);
    }
}

void print_nodes(node *n, int k) {
    for(int i = 0;i < k;i++)
        printf("|");
    printf("%d\n",n->key);
    if(n->left != NULL)
        print_nodes(n->left,k + 1);
    if(n->right != NULL)
        print_nodes(n->right,k + 1);
}

void inorderprint_nodes(node *n) {
    if(n->left != NULL) inorderprint_nodes(n->left);
    printf("%d ",n->key);
    if(n->right != NULL) inorderprint_nodes(n->right);
}

void preorderprint_node(node *n) {
    printf("%d ",n->key);
    if(n->left != NULL) inorderprint_nodes(n->left);
    if(n->right != NULL) inorderprint_nodes(n->right);
}

void postorderprint_node(node *n) {
    if(n->left != NULL) inorderprint_nodes(n->left);
    if(n->right != NULL) inorderprint_nodes(n->right);
    printf("%d ",n->key);
}

node *minimum(node *n) {
    if(n->left != NULL)
        return minimum(n->left);
    return n;
}

node *maximum(node *n) {
    if(n->right != NULL)
        return maximum(n->right);
    return n;
}

node *search(node *n,int val) {
    if(n->key == val)
        return n;
    if(val < n->key) {
        if(n->left == NULL) return NULL;
        return search(n->left, val);
    }
    else {
        if(n->right == NULL) return NULL;
        return search(n->right, val);
    }
}

node *prev(node *bt,node *n) {
    if(n->left != NULL)
        return maximum(n->left);
    node *y = n->parent;
    while(y != NULL || n == y->left) {
        n = y;
        y = y->parent;
    }
    return y;
}

node *next(node *bt,node *n) {
    if(n->right != NULL)
        return minimum(n->right);
    node *y = n->parent;
    while(y != NULL && n == y->right) {
        n = y;
        y = y->parent;
    }
    return y;
}

node *delete(node *root, int k) {
    if(root == NULL)
        return root;
    if(k < root->key)
        root->left = delete(root->left,k);
    else if(k > root->key)
        root->right = delete(root->right,k);
    else if(root->left != NULL && root->right != NULL) {
        root->key = minimum(root->right)->key;
        root->right = delete(root->right,root->key);
    }
    else {
        if(root->left != NULL) {
            root = root->left;
        }
        else if(root->right != NULL) {
            root = root->right;
        }
        else {
            root = NULL;
        }
    }
    return root;
}

void destruction(node *n) {
    if(n->left != NULL) destruction(n->left);
    if(n->right != NULL) destruction(n->right);
    free_node(n);
}

int depth_difference(node *n) {
    if(n == NULL) return 0;
    else return max(1 + depth_difference(n->left),1 + depth_difference(n->right));
}

int deepest_leaf_value(node *n) {
    if(n->left == NULL && n->right == NULL)
        return n->key;
    if(depth_difference(n->left) > depth_difference(n->right))
        return deepest_leaf_value(n->left);
    else
        return deepest_leaf_value(n->right);
}

int vertex_number(node *n) {
    return 1 + ((n->left != NULL) ? vertex_number(n->left) : 0) + ((n->right != NULL) ? vertex_number(n->right) : 0);
}

int non_terminal_number(node *n) {
    return 1 + ((n->left == NULL && n->right == NULL) ? -1 : ((n->left != NULL) ? non_terminal_number(n->left) : 0) + ((n->right != NULL) ? non_terminal_number(n->right) : 0));
}

int max_depth(node *n) {
    if(n->left == NULL && n-> right)
        return 0;
    return max(depth_difference(n->left) + depth_difference(n->right),max(max_depth(n->left), max_depth(n->right)));
}

bool BTree_check(node *n) {
    if(abs(depth_difference(n->left) - depth_difference(n->right)) <= 1) return true;
    return false;
}