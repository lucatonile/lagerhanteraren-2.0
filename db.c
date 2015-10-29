#include "db.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct db
{
  tree_t *goods; 
};


db_t  *db_new(){
  db_t *db = calloc(1,sizeof(db));
  db->goods = tree_new();

  return db;
}

good_t * db_get_good_at_index(db_t *db,int i){
  good_t *good = tree_get_inorder(db->goods,i);
  return good;
}

good_t * db_get_good_with_key(db_t *db,char *name){
    good_t *good = (good_t *)tree_get(db->goods,name);
    return good;
}

void db_remove_good_at_index(db_t *db, int i, bool dealloc){
  good_t *g = db_get_good_at_index(db,i);
  void *removed_good = NULL;

  tree_remove(&db->goods,good_get_name(g),&removed_good);
  if(dealloc)
  good_dealloc(removed_good);
}

void db_remove_good(db_t *db,char *key, bool dealloc){
  void *removed_good = NULL;
  tree_remove(&db->goods,key,&removed_good);

  if(dealloc)
  good_dealloc(removed_good);
}





void db_insert_good(db_t *db,good_t *good){
	
  tree_insert(&db->goods,good_get_name(good),good);
}


int db_get_good_count(db_t *db){
  return tree_size(db->goods);
}

tree_t * db_get_goods(db_t *db){
  return db->goods;
}


void dealloc_function(void *g) {
  good_t *good = (good_t *)g; 
  good_dealloc(good);
}
void db_dealloc(db_t *db){
  tree_dealloc(db->goods,&dealloc_function);
  free(db);
}



