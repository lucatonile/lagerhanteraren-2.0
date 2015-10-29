#ifndef __db_h__
#define __db_h__


#include "good.h"
#include "tree.h"

typedef struct db db_t;


/// \file db.h
/// \author Casper Strömberg
/// \version 1.0
/// \date 2015-10-12


/// Create new database 
/// \returns empty db
db_t  *db_new();

/// Deallocate db
/// Deallocate the database and all the data in it
/// \param db pointer to the database
void db_dealloc(db_t *db);

/// Get a db with good in alphabetical order at index i
/// Example:
/// database with goods that has the names:
/// alpha beta charlie delta
/// db_get_good_at_index(db,0) = alpha
/// db_get_good_at_index(db,2) = charlie
///
/// \param db pointer to the database
/// \param i index for the element you want
/// \returns pointer to the good at the provided index in the provided database
good_t * db_get_good_at_index(db_t *db,int i);


/// Get good by their name
/// \param db pointer to database
/// \param pointer to the name of the good you want
/// \returns pointer to the good with the provided name
good_t * db_get_good_with_key(db_t *db,char *name);

/// Get the entire tree with goods from db
/// \param db pounter to the databse
/// \returns pointer to tree with goods
tree_t * db_get_goods(db_t *db);

/// Returns how many goods there is in a database
/// \param db pointer to the database
/// \returns the total count of goods in the provided databse
int db_get_good_count(db_t *db);

/// Insert a good into the database
/// \param db pointer to the databse where you want to insert the good
/// \param good the good that you want to insert
void db_insert_good(db_t *db,good_t *good);

/// Remove good at inorder possition 
/// like db_get_good_at_index but remove good instead
/// \param db pointer to databse
/// \i index for the element to be deleted
/// \dealloc set true if you want the good to be dealloced else set to false
void db_remove_good_at_index(db_t *db, int i, bool dealloc);

/// Remove good with key
/// like db_get_good_with_key but remove
/// \param db pointer to the database
/// \param key key to the good to be deleted
/// \dealloc set true if you want the good to be dealloced else set to false
void db_remove_good(db_t *db,char *key,bool dealloc);








#endif