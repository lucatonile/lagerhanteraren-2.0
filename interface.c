#define _GNU_SOURCE
#include "interface.h"
#include "db.h"
#include "good.h"
#include "shelf.h"
#include "list.h"
#include "tree.h"
#include "pallet.h"
#include "input.h"
#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include  <ctype.h>



//TEST

///1 ADD GOOD
void add_goods_interf(db_t *db){
  char *name    =   Ask_name();
  good_t *good  =   db_get_good_with_key(db,name);

  if(good == NULL){
    //create new good
    char *desc   =  Ask_desc();
    int price    =  Ask_price();

    good = good_create(name,desc,price);
    db_insert_good(db,good);
    db_record_add(db,good);

  }else{
    free(name);
    puts("Hittade samma vara i databasen.");
    puts("Använder samma beskrivning och pris.");
    printf(" -- Beskrivning: %s \n",good_get_desc(good));
    printf(" -- Pris: %d \n",good_get_price(good));
  }
  //we have good 
  //now insert inte shelf 
    shelf_t *shelf = Ask_shelf(); /// \BUG mem leak //SOME REASON
    good_insert_shelf(&good,shelf);
}

///2 remove good

void remove_goods_interf(db_t *db){
  print_list_goods(db);
  int i = Ask_int("Välj en vara att radera:");

  //print shelves with id

  
 good_t *good =  db_get_good_at_index(db,i-1);
  //välj en hylla att radera
  //osv
 
 print_shelves(good_get_shelves(good));


 int index = Ask_int("Välj en hylla att radera:");

 list_t *list = good_get_shelves(good);
 list_remove(&list,index-1,(dealloc_function) shelf_dealloc);
    
    if(list_length(list) == 0){
        db_record_remove(db,good);
        db_remove_good(db, good_get_name(good), true);
    }

  
    

}



///3 edit good 

void edit_good_interf(db_t *db){

  print_list_goods(db);
  int i = Ask_int("Välj en vara att redigera:");
  good_t *good =  db_get_good_at_index(db,i-1);
    if(good == NULL){
        edit_good_interf(db);
    }
    good_t *old = good_copy(good);
    
  print_good(good,false);

  char opt = Ask_char("Vad vill du redigera? \n[N]amn\n[B]eskrivning\n[P]ris\n[A]vbryt\n\n");
  opt = toupper(opt);
    
  switch(opt){
    case 'N':
      printf("\nNuvarande namn:%s\n",good_get_name(good));
      char *new_name = Ask_str("Nytt namn:");
      db_remove_good(db,good_get_name(good),false);
      good_set_name(&good,new_name);
      db_insert_good(db,good);
      db_record_edit(db,old,good);
      good_dealloc(old);
    break; 

    case 'B':
      printf("\nNuvarande beskrivning:%s\n",good_get_desc(good));
      char *desc = Ask_str("Ny beskrivning:");
      good_set_desc(&good,desc);
      db_record_edit(db,old,good);
      good_dealloc(old);
      break;
     case 'P':
      printf("Nuvarande pris:%d\n",good_get_price(good));
      int price = Ask_int("Nytt pris:");
      good_set_price(&good,price);
      db_record_edit(db,old,good);
      good_dealloc(old);
     break; 

     case 'A':
       good_dealloc(old);
     return;
     break;

     default: 
     edit_good_interf(db);
     break;

  }



}


/// 4 UNDO

void regret_action_interf(db_t *db){
    undo(db);
}

/// 5 list 
void list_goods_interface(db_t *db){
  print_list_goods(db);
  int i = Ask_int("Välj en vara:");

  good_t *g = db_get_good_at_index(db,i-1);
  if(g != NULL){
    print_good(g,true);
  }

 

}






////////////////////////////////////////////////////////////////////////////////////////////////





















void shopping_interf(db_t *db){
    pallet_t *pallet = db_get_pallet(db);
    
    print_pallet(pallet);
  
  if(db_get_good_count(db) > 0){
    puts("\nVaror i databasen: ");
    print_list_goods(db);
  }else{
      puts("Inga varor i databasen.");
      return;
  }
   

  int i = Ask_int("\nVälj en vara att packa på pallen: ");

  while(i >= 0 && i > db_get_good_count(db)){
        i = Ask_int("Felaktigt index, försök igen.\n");
  }
  
  good_t *good = db_get_good_at_index(db, (i-1));

    
  printf("\nNamn: %s", good_get_name(good));
    printf("\nAntal: %d", good_get_total_count(good));
    
    
    char amount_question[126];
    sprintf(amount_question,"\n\nVälj antal (1-%d):",good_get_total_count(good));
    int count = Ask_int(amount_question);
  
  while(1){
    
    if(count <= good_get_total_count(good) && count > 0)
      break;
    
    if(count > good_get_total_count(good))
      printf("\nFinns tyvärr inte så många %s på lager! Var god välj färre.\n", good_get_name(good));

    count = Ask_int("");
  }
    
    pallet_add_good(&pallet, &good, count);
    
    char choice = Ask_char("\nVill du packa en till vara?[j]a/[n]ej");
    choice = toupper(choice);
  
    while(1){
      if(choice == 'J'){
	shopping_interf(db);
	break;
      }
      else if (choice == 'N'){
	print_pallet_shelves(pallet);
	break;
      }

      else
	choice = Ask_char("\nVill du packa en till vara?[j]a/[n]ej");
        choice = toupper(choice);
    }
}

void print_welcome(){

}
