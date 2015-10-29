#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//V1.2

struct tree_el{
	struct tree_el *left;
	struct tree_el *right;
	void *data;
	char *key;
};
   
struct tree{
	struct tree_el *root_node; 
	int count;
};

tree_t *tree_new(){
	tree_t *tmp = calloc(1,sizeof(tree_t));
	tmp->count = 0;
	return tmp;
}



int tree_size(tree_t *tree){
	return tree->count;
}

bool tree_insert(tree_t **tree,char *key, void *data)
{
	//copy key to mem
	char *copied_key = calloc(1,strlen(key)+1);
	strcpy(copied_key,key);
	tree_el_t *node = (tree_el_t *) calloc(1,sizeof(tree_el_t));
	
	node->data = data;
	node->key = copied_key;


	node->right = NULL;
	node->left = NULL;

	if((*tree)->root_node == NULL){
		(*tree)->root_node = node;
	}else{
		tree_el_t *current_node = (*tree)->root_node;
		
		while(1){
			if(strcmp(node->key,current_node->key) <= 0){
				if(current_node->left == NULL){
					current_node->left = node;
					break;
				}
				current_node = current_node->left; 
			}else{
				if(current_node->right == NULL){
					current_node->right = node;
					break;
				}
				current_node = current_node->right;
			}
		}
	}
	(*tree)->count += 1;
	return true;
}

void * tree_get(tree_t *tree,char *key){
	tree_el_t *current_node = tree->root_node;

	while(1){
		if(current_node == NULL){
			return NULL;
		}
		int comp = strcmp(key,current_node->key);
		if(comp == 0){
			//equal 
			return current_node->data;
		}else if(comp < 0){
			current_node = current_node->left;
		}else if(comp > 0) {
			current_node = current_node->right;
		}
	}

}

void print_node (tree_el_t *node){
	if(node == NULL){
		return;
	}
	printf("left %p right %p",node->left->key,node->right->key);
	if(node->left != NULL){
		print_node(node->left);
	}
	if(node->right != NULL){
		print_node(node->right);
	}
}

int node_depth(tree_el_t *node){
	if(node == NULL){
		return 0;
	}else{
		int left_depth = node_depth(node->left);
		int right_depth = node_depth(node->right);
		if(left_depth < right_depth){
			return right_depth+1;
		}else{
			return left_depth+1;
		}

	}
}
int tree_depth(tree_t *tree){
	return node_depth(tree->root_node);

}


tree_el_t **min_node(tree_el_t **node){
	if((*node)->left == NULL){
		return node;
	}else{
		return min_node(&(*node)->left);
	}
}

void tree_free_element(tree_el_t *node){
	free(node->key);
	free(node);
	node = NULL;

}

bool tree_remove_element(tree_el_t **current_node,char *key, void **elem){

	tree_el_t *successor;

	while(1){
		if(*current_node == NULL){
			return false;
		}

		printf("COMP: %s  %s",key,(*current_node)->key);


		int comp = strcmp(key,(*current_node)->key);
		if(comp == 0){
		  
//we found it
			//delete 

			printf("SET ELEM:%s",(*current_node)->key);
			*elem = (*current_node)->data;
			printf("SET ELEM:%p",elem);
			printf("SET ELEM:%p",*elem);
			
			if((*current_node)->left == NULL && (*current_node)->right == NULL){
				//no children
				//tree_free_element((*current_node));
			  

				tree_free_element(*current_node);
				*current_node = NULL;
				
			}else if((*current_node)->left != NULL && (*current_node)->right != NULL){
				//two children 
			
				tree_el_t **s = min_node(&(*current_node)->right);

				
				free((*current_node)->key);//free key
				(*current_node)->key = (*s)->key;//copy pointers to data
				(*current_node)->data = (*s)->data;//copy pointers to data
				
				free(*s);//free struct
				



 				
			}else if((*current_node)->left != NULL){
				//only left children
                successor = (*current_node)->left;
				tree_free_element(*current_node);
				*current_node = successor;

			}else if((*current_node)->right != NULL){
				//only right children
                successor = (*current_node)->right;
				tree_free_element(*current_node);
				*current_node = successor;
			}


			return true;
			
		}else if(comp < 0){
			current_node = &(*current_node)->left;
		}else if(comp > 0) {
			current_node = &(*current_node)->right;
		}
		
	}
}


void inorder(tree_el_t *node,int *i,void (*f)(void *,int*)) {
   if (node != NULL) {

      inorder(node->left,i,f);
      (*i)++;
      f(node->data,i);
      inorder(node->right,i,f);
   }
}

void tree_traverse_in_order(tree_t *tree, void (*f)(void *,int *) ){
	int i = 0;
	inorder(tree->root_node,&i,f);
}


void tree_get_inorder_help(tree_el_t * p, int* i, tree_el_t **result) {
  if(p == NULL) return;
  tree_get_inorder_help(p->left, i,result);

  if((*i)-- == 0) { 
    *result = p;
    return;  
  } 
  tree_get_inorder_help(p->right,i, result);


}



void *tree_get_inorder(tree_t *tree,int n){
	tree_el_t *res = NULL;
	tree_get_inorder_help(tree->root_node,&n,&res);

	if(res == NULL)
		return NULL;

	return res->data;
}
tree_el_t *tree_get_inorder_elem(tree_t *tree,int n){
	tree_el_t *res = NULL;
	tree_get_inorder_help(tree->root_node,&n,&res);

	if(res == NULL)
		return NULL;

	return res;
}



bool tree_remove(tree_t **tree,char *key, void **elem){
  

	tree_el_t **current_node = &(*tree)->root_node;
	(*tree)->count--;
	return	tree_remove_element(current_node,key,elem);

}


void tree_dealloc(tree_t *tree,void dealloc_function(void *) ){

	while(tree_size(tree) > 0){
		tree_el_t *el = tree_get_inorder_elem(tree,0);
	
		void *elem = NULL;
		if(tree_remove(&tree,el->key,&elem))
		dealloc_function(elem); 
		
		
		//send to dealloc function
	}
	//all elements dealloced 
	//dealloc tree
	free(tree);
		
	//DONE 
	
}

//http://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console
//print tree
//only for debug
int _print_t(tree_el_t *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (tree == NULL) return 0;

   
  
    char *m = (char *)tree->key; 
    sprintf(b, "(-%c-)", m[0]);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);


    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }

    return left + width + right;
}

int print_t(tree_el_t *tree)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);

    return 0;
}

void tree_debug(tree_t *tree){
	print_t(tree->root_node);
}

/*
static inline unsigned myrandomlt26() {
   long l;
   do { l = random(); } while (l>=(RAND_MAX/26)*26);
   return (unsigned)(l % 26);
}
void print_data(void *data){
	printf("%s\n", (data));
}


int main(){
	tree_t *tree = tree_new();
	
	tree_insert(&tree,"M","M");
	tree_insert(&tree,"F","F");
	tree_insert(&tree,"A","A");
	tree_insert(&tree,"B","B");
	tree_insert(&tree,"L","L");
	tree_insert(&tree,"Z","Z");
	tree_insert(&tree,"X","X");
	
	print_t(tree->root_node);

	puts("REMOVE M"); 

	void *f;
	tree_remove(&tree,"M",&f);
	print_t(tree->root_node);

	puts("REMOVE X"); 
	tree_remove(&tree,"X",&f);
	print_t(tree->root_node);

	puts("REMOVE F"); 
	tree_remove(&tree,"F",&f);
	print_t(tree->root_node);

	//tree_remove(&tree,"M",&f);
	//tree_remove(&tree,"M",&f);
<<<<<<< HEAD


	
	
=======


	
	
>>>>>>> lucas


	puts("REMOVE X");
	tree_remove(&tree,"X",&f);
	print_t(tree->root_node);

	inorder(tree->root_node,&print_data);


return 0;
}
*/	









