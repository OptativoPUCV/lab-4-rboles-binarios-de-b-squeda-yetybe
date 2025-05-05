#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{

    TreeMap * map = (TreeMap*)malloc(sizeof(TreeMap));
    if ( map == NULL) return NULL;

    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map;
}

void insertTreeMap(TreeMap * tree, void* key, void * value)
{
    if (tree == NULL || key == NULL || value == NULL )return;
    if (searchTreeMap(tree , key) != NULL) return;
    
    TreeNode * new = createTreeNode(key , value);
    
    if (tree->root == NULL)
    {
        tree->root = new;
        tree->current = new;
        return;
    }
    else
    {
        TreeNode * temp = tree->root;
        
        while (1)
        {
            if (tree->lower_than(key, temp->pair->key))
            {
                if (temp->left == NULL)
                {
                    temp->left = new;
                    new->parent = temp;
                    tree->current = new;
                    break;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else if (key > temp->pair->key)
            {
                if (temp->right == NULL)
                {
                    temp->right = new;
                    new->parent = temp;
                    tree->current = new;
                    break;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
    }
}



TreeNode * minimum(TreeNode * x)
{
    if (x == NULL) return NULL;
    while( x->left != NULL)
    {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
   if (node == NULL) return;
   TreeNode * parent = node->parent;

   if(node->left == NULL && node->right == NULL) 
   {
    if(node != tree->root) 
    {
        if(parent->left == node)
            parent->left = NULL;
        else
            parent->right = NULL;
    } 
    else 
    {
        tree->root = NULL;
    }

    free(node);
}

else if(node->left == NULL || node->right == NULL) 
{
    TreeNode* child;
    if(node->left != NULL)
        child = node->left;
    else
        child = node->right;

    if(node != tree->root) 
    {
        if(parent->left == node)
            parent->left = child;
        else
            parent->right = child;
        child->parent = parent; 
    } 
    else 
    {
        tree->root = child;
        child->parent = NULL;  
    }

    free(node);
}

else 
{
    TreeNode* proximo = minimum(node->right);
    void * proximKey = proximo->pair->key;
    void* proximValue = proximo->pair->value;
    removeNode(tree, proximo);  
    node->pair->key = proximKey;
    node->pair->value = proximValue;
}
}


void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    if (tree == NULL || key == NULL) return NULL;

    TreeNode * aux = tree->root;

    while (aux != NULL)
    {
        if (is_equal(tree, key, aux->pair->key)) {
            tree->current = aux;
            return aux->pair;
        }

        if (tree->lower_than(key, aux->pair->key)) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    return NULL; 
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
