
#include "shelf.h"				
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct shelf
{
  char alf; 
  int num; 
  int count;
};

shelf_t *shelf_create(char *place,int count){ // används vid inmatning av lagerhylla{   
  // testar ifall den första char är en bokstav
  if(!isalpha(place[0])){
    return NULL;
  } 

  //testar ifall de andra char är siffror
  int i = 1;
  while(place[i] != 0){
    if(!isdigit(place[i])){
      return NULL;
      }
    i++;
  }  

  //test if the length make sence 
  if(i < 2){
    return NULL;
  }


    shelf_t *plc = calloc(1,sizeof(shelf_t));
    plc->alf = place[0];
  
    plc->num = atoi(&place[1]);
    plc->count = count;
  return plc;
}

int shelf_cmp(shelf_t *s1,shelf_t *s2){
  if(s1->alf < s2->alf){
    return -1; 
  }else if(s1->alf > s2->alf){
    return 1;
  }else{
    //alf is equal
      if(s1->num < s2->num){
        return -1; 
      }else if(s1->num > s2->num){
        return 1;
      }
  }
  return 0;
}

void shelf_dealloc(shelf_t *shelf){
  free(shelf);
}

void shelf_dealloc_function(void *d){
  shelf_t *shlf = (shelf_t *)d;
  shelf_dealloc(shlf);
}

void shelf_list_dealloc(list_t *list){
    list_dealloc(list,&shelf_dealloc_function);
      
}

char shelf_get_alf(shelf_t *shelf){
  return shelf->alf;
}
int shelf_get_num(shelf_t *shelf){
  return shelf->num;
}
int shelf_get_count(shelf_t *shelf){
  return shelf->count;
}


void shelf_set_count(shelf_t **shlf,int count){
  (*shlf)->count += count;
}

int cmpfunc (const void * a, const void * b)
{
  shelf_t *cmp1 = (shelf_t *)a;
  shelf_t *cmp2 = (shelf_t *)b;
  
  return cmp1->count - cmp2->count;
}

void shelf_array_sort(shelf_t *shelf_list,int lngth){
  qsort(shelf_list,lngth,sizeof(shelf_t *),cmpfunc);
}

