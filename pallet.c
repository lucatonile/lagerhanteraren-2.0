
#include <stdio.h>
#include <stdlib.h>

#include "pallet.h"
#include "shelf.h"
#include "list.h"


struct pallet
{
  list_t *pallet_items; 
};



pallet_t *pallet_new()
{
	pallet_t *tmp = calloc(1,sizeof(pallet_t));
	tmp->pallet_items = list_new();
	return tmp;
}	

void pallet_add_good(pallet_t **pallet, good_t **good, int amount){
	list_t *shelves = good_get_shelves(*good);
	int lngth = list_length(shelves); 

	shelf_t **arr = (shelf_t **)list_array(shelves);

	while(amount > 0){
		shelf_t *biggest = NULL;
		int biggest_index = -1;
		for(int i = 0; i<lngth; i++){
			if(biggest == NULL || shelf_get_count(biggest) < shelf_get_count(arr[i])){
				biggest = arr[i];
				biggest_index = i;
			}
		} 
		//push
		if(biggest != NULL){
			if(amount < shelf_get_count(biggest)){
				shelf_set_count(&biggest,shelf_get_count(biggest)-amount);
				list_append(&(*pallet)->pallet_items,biggest);
			}
			
			
		}
		
	}


	for(int i = 0; i<lngth; i++){
		shelf_t *shelf = arr[i];
		printf("<%c%d>",shelf_get_alf(shelf),shelf_get_num(shelf));
  printf("%17dst\n",shelf_get_count(shelf));
	}

	shelf_array_sort(*arr, lngth);
	
	for(int i = 0; i<lngth; i++){
		shelf_t *shelf = arr[i];
		printf("<%c%d>",shelf_get_alf(shelf),shelf_get_num(shelf));
  printf("%17dst\n",shelf_get_count(shelf));
	}


}