#ifndef __pallet_h__
#define __pallet_h__


#include "good.h"

typedef struct pallet pallet_t;


void pallet_add_good(pallet_t **pallet, good_t **good, int amount);





pallet_t *pallet_new();

void pallet_dealloc(pallet_t *pallet);

void pallet_add_good(pallet_t **pallet,good_t **good,int count);

void print_pallet(pallet_t *pallet);

void print_pallet_shelves(pallet_t *pallet);

int pallet_get_total_count(pallet_t *pallet);
int pallet_get_total_price(pallet_t *pallet);

#endif
