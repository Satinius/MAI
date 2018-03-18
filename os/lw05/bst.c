#include "bst.h"

BSTree * tree_create(void)
{
    BSTree * new_tree = (BSTree *)malloc(sizeof * new_tree);
    if (new_tree == NULL) return NULL;
    new_tree->root = NULL;
    new_tree->count = 0;
    return new_tree;
}

int bin_search(const BSTree * search_tree, ElemType item)
{
    const Node * search_node;
    search_node = search_tree->root;
    for(;;)
    {
        if (search_node == NULL) return 0;
        else if (item == search_node->data) return 1;
        else if (item > search_node->data) search_node = search_node->right;  
        else search_node = search_node->left;  
    }
}

int insert(BSTree * search_tree, ElemType item)
{
    Node * search_node, **new;
 
    new = &search_tree->root;
    search_node = search_tree->root;
 
    for(;;)
    {
        if(search_node == NULL)
        {
            search_node = *new = malloc(sizeof * search_node);
            if(search_node != NULL)
            {
                search_node->data = item;
                search_node->left = search_node->right=NULL;
                search_tree->count++;
                return 1;
            }
            else return 0;
        }
        else if(item == search_node->data) return 2;
        else if(item > search_node->data)
        {
            new = &search_node->right;
            search_node = search_node->right;
        }
        else
        {
            new = &search_node->left;
            search_node = search_node->left;
        }
    }
}
int _delete(BSTree * search_tree, ElemType item)
{
    Node ** q,*z;
     
    q=&search_tree->root;
    z=search_tree->root;
    //поиск удаляемого элемента
    for(;;)
    {
        if(z == NULL) return 0;
        else if(item == z->data) break;
        else if(item > z->data)
        {
            q = &z->right;
            z = z->right;
        }
        else
        {
            q = &z->left;
            z = z->left;
        }
    }       
     
    // непосредственное удаление элемента
    if(z->right == NULL) *q = z->left;
    else
    {
        Node * y = z->right;
        if(y->left == NULL)
        {
            y->left = z->left;
            *q-y;
        }
        else
        {
            Node * x=y->left;
            while(x->left != NULL)
            {
                y = x;
                x = y->left;
            }
            y->left = x->right;
            x->left = z->left;
            x->right = z->right;
            *q=x;
        }
    }
 
    search_tree->count --;
    free(z);
    return 1;
}

void walk(const Node * search_node, int deep)
{
    if (search_node == NULL) return;
    walk(search_node->left, deep + 1);
    for (int i = 0; i < deep; i++)
        printf(" ");
    printf("%lf\n", search_node->data);
    walk(search_node->right, deep + 1);
}
void print(const BSTree * search_tree)
{
    walk(search_tree->root, 0);
}

bool is_empty(BSTree * search_tree)
{
    return search_tree->count;
}

void destroy_node(Node * search_node)
{
    if(search_node == NULL) return;
    destroy(search_node->left);
    destroy(search_node->right);
    free(search_node);
}
void destroy(BSTree * search_tree)
{
    destroy(search_tree->root);
    free(search_tree);
}