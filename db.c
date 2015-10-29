#include "db.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "pallet.h"

typedef struct action action_t;
struct action
{
    enum { NOTHING, ADD, REMOVE, EDIT } type;
    good_t *old;
    good_t *new; // EDIT
};



struct db{
  tree_t *goods;
  action_t action;
  pallet_t *pallet;
};


db_t  *db_new(){
  db_t *db = (db_t *)calloc(1,sizeof(db_t));
  db->goods = tree_new();
  db->action.type = NOTHING;
  db->action.old = NULL;
  db->action.new = NULL;
    
    db->pallet = pallet_new();
  return db;
}
pallet_t *db_get_pallet(db_t *db){
    return db->pallet;
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


  if(dealloc && removed_good != NULL)
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


void db_dealloc_record(db_t *db){
    db->action.new = NULL;
    
    if(db->action.old){
        good_dealloc(db->action.old);
        db->action.old = NULL;
    }
    db->action.type = NOTHING;
    
}

void db_record_add(db_t *db,good_t *old_good){
    db_dealloc_record(db);
    db->action.old = good_copy(old_good);
    db->action.type = ADD;
  
}

void db_record_remove(db_t *db, good_t *removed_good){
    db_dealloc_record(db);
    db->action.old = good_copy(removed_good);
    db->action.type = REMOVE;
    
}

void db_record_edit(db_t *db,good_t *old,good_t *new){
    db_dealloc_record(db);
    db->action.old = good_copy(old);
    db->action.new = new;
    db->action.type = EDIT;
     
}

bool undoable(db_t *db){
    return (db->action.type != NOTHING);
}
void undo(db_t *db){
    
    switch (db->action.type) {
        case ADD:
            db_remove_good(db, good_get_name(db->action.old), true);
            break;
        case REMOVE:
            db_insert_good(db, good_copy(db->action.old));
            break;
        case EDIT:
            good_assign(db->action.new,db->action.old);
            break;
            
        case NOTHING:
            puts("Nothing to undo");
            return;
            break;

    }
    
    db_dealloc_record(db);
    
}




void db_dealloc(db_t *db){
  tree_dealloc(db->goods,(dealloc_function)good_dealloc);

    
  pallet_dealloc(db->pallet);
  db_dealloc_record(db);
  free(db);
    
}
