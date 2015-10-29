#ifndef __shelf_h__
#define __shelf_h__

#include "list.h"

typedef struct shelf shelf_t;

/// \file shelf.h
/// \author Casper Strömberg
/// \version 1.0
/// \date 2015-10-12

/// Creates new good 
/// \param place raw input to the place where shelf should exist
/// \param count the count that the shelf should be
/// \returns the shelf that was created or NULL if place was bad formated 
shelf_t *shelf_create(char *place,int count);

/// Deallocate a shelf 
/// \param shelf a pointer to the shelf to be dealloced
void shelf_dealloc(shelf_t *shelf);

/// shelf list dealloc
/// applies shelf_dealloc on a linked list
/// \param list a pointer to a list to be deallocated
void shelf_list_dealloc(list_t *list);

/// shelf arrat sort
/// depricated
/// \bug does not work
void shelf_array_sort(shelf_t *shelf_list, int length);


/// get the char part of the shelf adress
/// \param shelf a pointer to the shelf 
/// \returns char with the char part
char shelf_get_alf(shelf_t *shelf);

/// get the num part of the shelf adress
/// \param shelf a pointer to the shelf 
/// \returns int with the num part
int shelf_get_num(shelf_t *shelf);

/// get the count of a shelf
/// \param shelf a pointer to the shelf 
/// \returns int with the count
int shelf_get_count(shelf_t *shelf);


/// compare two shelves adresses in alphabetical order
/// \param s1 a pointer to a shelf
/// \param s2 a pointer to a shelf
int shelf_cmp(shelf_t *s1,shelf_t *s2);



/// set the count of a shelf
/// \param shlf a pointer to a pointer of the shelf to be altered 
/// \param count the value to be set as count

void shelf_set_count(shelf_t **shlf,int count);




#endif