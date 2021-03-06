#include "good.h"
#include <stdlib.h>
#include "shelf.h"
#include <stdio.h>
#include <string.h>

struct good
{
  char *name;
  char *desc;
  int price; 
  list_t *shelves; 

};



good_t * good_alloc(){
  good_t *tmp = calloc(1, sizeof(good_t));
  return tmp;
}


good_t * good_create(char *name, char *desc, int price){
  //create new good without any shelves
  good_t *new_good = (good_t *)calloc(1,sizeof(good_t)); 
  new_good->name = name;
  new_good->desc = desc;
  new_good->price = price; 
  new_good->shelves = list_new();
  return new_good;
}



void good_dealloc(good_t *good){

  free(good->name);
  free(good->desc);
  shelf_list_dealloc(good->shelves);
  free(good);
}




void good_insert_shelf(good_t **good,shelf_t *shelf){
  //TODO:
  //loop trough and see if shelf is present
  //if present add count 
  //if not, just append

  //GROVT ÖVERGREPP PÅ HASTIGHETEN
  // ;{}
  int i = list_length((*good)->shelves);
  while(i--){  

    shelf_t *s1 = list_get((*good)->shelves,i);

    if(shelf_cmp(shelf,s1) == 0){
      //equal 
      shelf_set_count(&s1,shelf_get_count(shelf));
      return; 
    }
  }
  list_append(&(*good)->shelves,shelf);
}



char *good_get_name(good_t *good){
  return good->name;
}
char *good_get_desc(good_t *good){
  return good->desc;
}
int good_get_price(good_t *good){
  return good->price;
}

list_t *good_get_shelves(good_t *good){
  return good->shelves;
}


int good_get_total_count(good_t *good){
  // good->shelves->count ++ good->shelves->next->count

  int n = 0;
  
  shelf_t **shelf_list = (shelf_t**)list_array(good->shelves);

  for(int i = 0; i < list_length(good->shelves); i++){
    n += shelf_get_count(shelf_list[i]);
  }

  free(shelf_list);
  return n;
}


void good_set_name(good_t **good, char *name){
  free((*good)->name);
  (*good)->name = name;
}


void good_set_desc(good_t **good, char *desc){
  free((*good)->desc);
  (*good)->desc = desc;
}

void good_set_price(good_t **good, int price){
  (*good)->price = price;
}


good_t *good_copy(good_t *good){
    good_t *new_good = (good_t *)calloc(1,sizeof(good_t));
    new_good->name = (char *)calloc(1,strlen(good->name)*sizeof(char));
    new_good->desc = (char *)calloc(1,strlen(good->name)*sizeof(char));
    *new_good->name = *good->name;
    *new_good->desc = *good->desc;
    
    new_good->price = good->price;
    new_good->shelves = list_new();
    
    return new_good;
}

void good_assign(good_t *good1, good_t *good2){
    *good1 = *good2;
    
}
