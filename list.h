#ifndef __list_h__
#define __list_h__

 #include <stdbool.h>

typedef struct list list_t;
typedef struct list_el list_el_t;


/// Linked list


/// \file list.h
///
/// \author Tobias Wrigstad
/// \version 1.0
/// \date 2015-08-28
/// \bug None known. But this code is untested so there are likely bigs in it. 


/// Creates a new list
///
/// \returns: empty list
//void (*dealloc)(void *data)
list_t *list_new();

/// Inserts a new element at the end of the list
///
/// \param list pointer to the list
/// \param elem the integer to be appended
void list_append(list_t **list, void *data);

/// Inserts a new element at the end of the list
///
/// \param list pointer to the list
/// \param elem the integer to be prepended
void list_prepend(list_t **list, void *data);

/// Inserts a new element at a given index. 
///
/// Valid indexes are [0..size]. 
///
/// Example:
///
/// list_t *l = list_new(); // l == []
/// list_insert(l, 0, 42);  // l == [42]
/// list_insert(l, 0, 43);  // l == [43, 42]
/// list_insert(l, 1, 44);  // l == [43, 44, 42]
/// list_insert(l, 5, 45);  // l == [43, 44, 42]
///
/// The last case fails (and returns false) because
/// size is 3, meaning 5 is not a valid index. 
///
/// Note that insert at index 0 is the same as prepend 
/// and insert index size is the same as append. 
///
/// Negative indexes should be supported:
///
/// list_insert(l, 1, -45);       // l == [43, 44, 42, 45]
///
/// A positive index can be calculated from a 
/// negative like this: pos_i = size + 1 - neg_i.
/// 
/// \param list  pointer to the list
/// \param index the index for elem to be inserted at
/// \param elem  the integer to be prepended
/// \returns true if succeeded, else false
bool list_insert(list_t **list, int index, void *data);

/// Removes an element from a list.
///
/// Example: (assume l == [43, 44, 42, 45])
///
/// int elem;
/// list_remove(l, 1, &elem);  // l = [43, 42, 45], elem == 44
/// list_remove(l, -1, &elem); // l = [43, 42], elem == 45
///
/// \param list  pointer to the list
/// \param index the index to be removed
/// \param elem a pointer to where the element can be stored
/// \returns true if succeeded, else 
/// 
bool list_remove(list_t **list, int index,void **elem);

/// Returns the element at a given index
/// \param list  pointer to the list
/// \param index the index to be returns
/// \returns a pointer to the element at index index
void *list_get(list_t *list, int index);

/// A convenience for list_get(list, 0)
void *list_first(list_t *list);

/// A convenience for list_get(list, -1)
void *list_last(list_t *list);

/// Returns the length of the list. 
/// \param list the list
/// \returns the length of list
int list_length(list_t *list);

/// Traverse the list with the provided function
/// \param list the list
/// \param f pointer to a function that should be used in the traverse
void list_traverse(list_t *list,void (*f)(void *,int));

void print_list(list_t *list);


/// Dumps the linked list as a array
/// \param list the list
/// \return a pointer to a void pointer where the list starts
void **list_array(list_t *list);


void list_dealloc(list_t *list, void dealloc_function(void *));

#endif
