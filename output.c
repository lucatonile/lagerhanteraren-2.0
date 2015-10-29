#include "output.h"
#include "good.h"
#include "db.h"

#include <stdio.h>
#include <stdlib.h>
#include  <ctype.h>


void print_shelf_and_index(void *shelf, int i){
  
    if(shelf_get_count(shelf)== 0){
        i--;
    }else{
        if(i != -1) printf("%d                 ",i+1);
        printf("<%c%d>",shelf_get_alf(shelf),shelf_get_num(shelf));
        printf("%17dst\n",shelf_get_count(shelf));
    }
    
 
}

void print_good_name_and_index(void *good, int *index){
  good_t *g = good;
  printf("%d. %s\n",*index,good_get_name(g));

}


void print_shelf(shelf_t *shelf){
	print_shelf_and_index(shelf,-1);
}


void print_shelves(list_t *shelves){

  puts("Varorna finns på hyllorna:");
  printf("\nId:               Hylla:               Antal:\n");
  list_traverse(shelves,&print_shelf_and_index);

}

void print_good(good_t *good,bool shelves){

  printf("\nNamn:%s\nBeskrivning:%s\nPris:%d\n",
  			good_get_name(good),
  			good_get_desc(good),
  			good_get_price(good));

  if(shelves) print_shelves(good_get_shelves(good));
}



void print_list_goods(db_t *db){
  tree_traverse_in_order(db_get_goods(db),&print_good_name_and_index);
}
