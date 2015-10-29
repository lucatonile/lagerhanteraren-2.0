#ifndef __system_h__
#define __system_h__

#include "shelf.h"
#include "list.h"


typedef struct good good_t;


/// \file good.h
/// \author Casper Strömberg
/// \version 1.0
/// \date 2015-10-12


/// Creates new good 
/// \param name pointer to name of the good
/// \param desc pounter to the description of the good
/// \param price the price of the good
/// \returns the good that was created
good_t * good_create(char *name, char *desc, int price);

/// Insert shelf into good
/// inserts a shelf into a good
/// if shelf allready exists, add the shelves count
/// \param good pointer to pointer to good that should be used
/// \param shelf pointer to shelf that is to be inserted
void good_insert_shelf(good_t **good,shelf_t *shelf);



//good get

/// Get name of a good
/// \param pointer to the good
/// \returns the name
char *good_get_name(good_t *good);

/// Get description of a good
/// \param pointer to the good
/// \returns the description
char *good_get_desc(good_t *good);

/// Get price of a good
/// \param pointer to the good
/// \returns the price
int good_get_price(good_t *good);

/// Deallocates a good
/// Deallocates a good and all the pointers in it
/// \param pointer to the good
void good_dealloc(good_t *good);

/// Get a linked list with all the shelves where the good exists
/// \param good pointer to the good
/// \returns a linked list with shelves
list_t *good_get_shelves(good_t *good);


//good set 

/// Set the name of a good
/// \param good pointer to pointer of the good to be altered
/// \param name the new name 
void good_set_name(good_t **good, char *name);

/// Set the description of a good
/// \param good pointer to pointer of the good to be altered
/// \param desc the new description 
void good_set_desc(good_t **good, char *desc);

/// Set the price of a good
/// \param good pointer to pointer of the good to be altered
/// \param price the new price 
void good_set_price(good_t **good,int price);



good_t * good_alloc();



good_t *good_copy(good_t *good);

void good_assign(good_t *good1, good_t *good2);






int good_get_total_count(good_t *good);






#endif

