#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>

/// Define struct tree in your .c file not here! (why?)
typedef struct tree tree_t;
typedef struct tree_el tree_el_t;

/// \file tree.h
///
/// \author Tobias Wrigstad
/// \version 1.0
/// \date 2015-08-28
/// \bug This file is partial. (On purpose.)


/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new();

void tree_dealloc(tree_t *tree,void dealloc_function(void *));

void * tree_get(tree_t *tree,char *key);
/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree);

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree);

bool tree_insert(tree_t **tree,char *key, void *data);


// remove element with key
// 
bool tree_remove(tree_t **tree,char *key, void **elem);

//get element n in order
void *tree_get_inorder(tree_t *tree,int n);

void tree_debug(tree_t *tree);

void tree_traverse_in_order(tree_t *tree, void (*f)(void *,int *) );



#endif