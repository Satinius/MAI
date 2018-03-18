#ifndef _BST_H_
#define _BST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FAILURE 1
#define SUCCESS 0

typedef double ElemType;

typedef struct _node {
    ElemType data;
    struct _node * left;
    struct _node * right; 
} Node;

typedef struct _tree {
    size_t count;
    Node * root;
} BSTree;

extern BSTree * tree_create(void);
extern int bin_search(const BSTree * search_tree, ElemType item);
extern int insert(BSTree * search_tree, ElemType item);
extern int _delete(BSTree * search_tree, ElemType item);
extern void walk(const Node * search_node, int deep);
extern void print(const BSTree * search_tree);
extern bool is_empty(BSTree * search_tree);
extern void traverse(const BSTree * search_tree);
extern void destroy_node(Node * search_node);
extern void destroy(BSTree * search_tree);
#endif