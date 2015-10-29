#ifndef __pallet_h__
#define __pallet_h__

#include "good.h"

typedef struct pallet pallet_t;

pallet_t *pallet_new();
void pallet_add_good(pallet_t **pallet, good_t **good, int amount);

#endif