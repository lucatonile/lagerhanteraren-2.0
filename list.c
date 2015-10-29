#include "list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 

struct list_el{
	void *data;
	struct list_el *next; 
};


struct list{
	int count; 
	struct list_el *last_el; 
	struct list_el *first_el;
};



int calculate_positive(int i,int size){
	return size + i + 1;
}


//void (*dealloc)(void *data)
list_t *list_new(){
	list_t *tmp = calloc(1,sizeof(list_t));
	tmp->count = 0;
	tmp->first_el = NULL;
	return tmp;
}

int list_length(list_t *list)
{
	return list->count;
}



list_el_t *list_get_item(list_t *list, int index){	
	if(index > list_length(list)){
		return NULL;
	}
	if(index < 0 && index != -1){
		index = calculate_positive(index,list_length(list));
	}
	//special case for last
	//speed increese 
	if(index == -1){
		return list->last_el;
	}

	list_el_t *curent_list_item = list->first_el;
	for(int i = 0; i<index; i++){
		if(curent_list_item->next == NULL){
			return NULL;
		}
		curent_list_item = curent_list_item->next;
	}

	return curent_list_item;
}

void * list_get(list_t *list, int index)
{	
	list_el_t *item = list_get_item(list,index);
	return item->data;
}


bool list_insert(list_t **list, int index, void *data)
{
	if(index < 0){
		index = calculate_positive(index,list_length(*list));
	}
	
	list_el_t *new_element = calloc(1,sizeof(list_el_t));
	new_element->data = data;

	if(index == 0){
		new_element->next = (*list)->first_el;
		(*list)->first_el = new_element;

	}else{
		list_el_t *head = list_get_item(*list,index-1);
		if(head == NULL){
			return false;
		}
		new_element->next = head->next;
		head->next = new_element;
	}

	(*list)->last_el = new_element;
	(*list)->count++;
	return true;		
}


void list_traverse(list_t *list,void (*f)(void *,int)){
	list_el_t *current_el = list->first_el;
	int i = 0;
	while(current_el != NULL){
		f(current_el->data,i);
		i++;
		current_el = current_el->next;
	}

}

void list_dealloc(list_t *list, void dealloc_function(void *)){
  list_el_t *current_el = list->first_el;
  while(current_el != NULL){
    dealloc_function(current_el->data);
    
    list_el_t *p = current_el;
    current_el = current_el->next;
    free(p);
  }
  free(list);
}

bool list_remove(list_t **list, int index, void **elem)
{
	if(index < 0){
		index = calculate_positive(index,(*list)->count);
	}

	if(index >=  (*list)->count){
		return false;
	}

	if(index == 0){
		
		*elem = (*list)->first_el->data;
		
		list_el_t *p = (*list)->first_el;
		
		(*list)->first_el = (*list)->first_el->next;
		
		free(p);

		
		
	}else{
		list_el_t *head = list_get_item(*list,index-1);
		if(head == NULL){
			//no element on index 
			return false; 
		}
		*elem = head->next->data;
		head->next = head->next->next;
		free(head->next);
	}

	(*list)->count--;
	
	return true;
}


///DEBUG FUNCTION
void print_list(list_t *list){
	list_el_t *curent_list_item = list->first_el;

	while(curent_list_item != NULL){
		char *s = curent_list_item->data;
		printf("ADRESS:%p DATA:%s POINTER:%p \n",curent_list_item, s,curent_list_item->next);
		curent_list_item= curent_list_item->next;
	}
}





void *list_first(list_t *list)
{
	return list_get(list,0);
}

void *list_last(list_t *list)
{
	return list_get(list,-1);
}

void list_append(list_t **list, void *data)
{
	list_insert(list,-1,data);
}
void list_prepend(list_t **list, void *data)
{
	list_insert(list,0,data);
}



void **list_array(list_t *list){
	int count = list_length(list);
	void **arr = calloc(1,sizeof(void *)*count);
	list_el_t *current_el = list->first_el;

	int i = 0;
	while(current_el != NULL){
		arr[i] = current_el->data;
		i++;
		current_el = current_el->next;
	}

	return arr;
}




