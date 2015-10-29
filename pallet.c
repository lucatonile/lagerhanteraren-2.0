#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "db.h"
#include "pallet.h"
#include "good.h"
#include "list.h"
#include "shelf.h"
#include "tree.h"
#include <stdbool.h>



typedef struct pallet_el pallet_el_t;
typedef struct pallet_shelf pallet_shelf_t;

struct pallet_shelf{
    shelf_t *shelf; //pointer to shelf
    int count; //the real count
};

struct pallet_el{
    good_t *good;
    list_t *shelves; //pointer to pallet_shelf
    int count;//total count in all shelves
};
  
struct pallet{
tree_t *pallet_tree;
};



pallet_el_t *pallet_el_new(){
  pallet_el_t *tmp = calloc(1, sizeof(pallet_el_t));
  tmp->good = NULL;
  tmp->shelves = list_new();
  return tmp;
}


pallet_t *pallet_new(){
  pallet_t *tmp = calloc(1, sizeof(pallet_t));
  tmp->pallet_tree = tree_new();
  return tmp;
}
void pallet_shelf_dealloc(pallet_shelf_t *pallet_shelf){
    free(pallet_shelf); //do not free the shelf itself
}

void pallet_el_dealloc(pallet_el_t *pallet_element){
    //do not free the good
    list_dealloc(pallet_element->shelves,(void (*)(void *))pallet_shelf_dealloc );
    free(pallet_element);
    
}
void pallet_dealloc(pallet_t *pallet){
    tree_dealloc(pallet->pallet_tree,(void (*)(void *))pallet_el_dealloc );
    free(pallet);
}

void pallet_add_good(pallet_t **pallet,good_t **good,int count){
    //determinate the shelves we need
    
    //dump ass array
    //now sort
    list_t *shelves_list = good_get_shelves(*good);
    shelf_t **shelves = (shelf_t **)list_array(shelves_list);
    shelf_array_sort(shelves, list_length(shelves_list));
    
    
    pallet_el_t *pallet_element = tree_get((*pallet)->pallet_tree,good_get_name(*good));
   
    
    if(pallet_element == NULL){
        pallet_element = pallet_el_new();
        pallet_element->good = *good;
        tree_insert(&(*pallet)->pallet_tree,good_get_name(pallet_element->good),pallet_element);
    }
    
    pallet_element->count += count;
    
    
    
    
    
    //shelves is sorted
    for(int i = 0; i<list_length(shelves_list);i++){
        //loop trough whole list with shelves
        pallet_shelf_t *p = calloc(1,sizeof(pallet_shelf_t));
        int shelf_count =shelf_get_count(shelves[i]);
      
        if(count <= shelf_count){
            shelf_set_count(&shelves[i], shelf_count-count);
            p->count = count;
        }else{
            p->count = shelf_count;
            shelf_set_count(&shelves[i], 0);
        }
        
        
        
        
        
        p->shelf = shelves[i];
        count -= p->count;
        

        if(p->count != 0){
            list_append(&pallet_element->shelves, p);//add shelf on pallet_el
        }else{
            pallet_shelf_dealloc(p);
        }
        
        
        if(count <= 0) break;
    }
    
    free(shelves);
}


int pallet_get_total_count(pallet_t *pallet){
    int total_count = 0;
    for(int i = 0; i<tree_size(pallet->pallet_tree);i++){
        pallet_el_t *pallet_element = (pallet_el_t *)tree_get_inorder(pallet->pallet_tree, i);
        total_count += pallet_element->count;
    }
    return total_count;
}

int pallet_get_total_price(pallet_t *pallet){
    int total_price = 0;
 
    for(int i = 0; i<tree_size(pallet->pallet_tree);i++){
        pallet_el_t *pallet_element = (pallet_el_t *)tree_get_inorder(pallet->pallet_tree, i);
        total_price += pallet_element->count * good_get_price(pallet_element->good);
    }
    return total_price;
}

void print_pallet_el(pallet_el_t *pallet_element,int *i){
    printf("%d.%s %dst \n",*i+1,good_get_name(pallet_element->good),pallet_element->count);
}

void print_pallet(pallet_t *pallet){
    puts("===== PALLET =====");
    printf("Pallet contains %d goods\n",pallet_get_total_count(pallet));
    printf("Pallet total price:%d\n",pallet_get_total_price(pallet));
    tree_traverse_in_order(pallet->pallet_tree, (void (*)(void *,int *))print_pallet_el);
    
    puts("\n=====        =====");
    
}


void print_pallet_shlf(pallet_el_t *pallet_element,int *i){
    
    for(int i = 0; i<list_length(pallet_element->shelves);i++){
        pallet_shelf_t *shlf = list_get(pallet_element->shelves, i);
        char *id = shelf_get_id(shlf->shelf);
        printf("%s (%d st %s)\n",id,shlf->count,good_get_name(pallet_element->good));
        free(id);
    }
}

void print_pallet_shelves(pallet_t *pallet){
    puts("===== PALLET =====");
    printf("Pallet contains %d goods\n",pallet_get_total_count(pallet));
    printf("Pallet total price:%d\n\n",pallet_get_total_price(pallet));
    tree_traverse_in_order(pallet->pallet_tree, (void (*)(void *,int *))print_pallet_shlf);
    puts("\n=====        =====");
    
}
