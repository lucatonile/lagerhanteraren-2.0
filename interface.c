#include "interface.h"
#include "db.h"
#include "good.h"
#include "shelf.h"
#include "list.h"
#include "tree.h"
#include "pallet.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>




void clear_stdin(){
  //fflush(stdin);
  while(getchar() != '\n');
}


void print_welcome() // skriver ut text, görs endast en gång
{
  puts("\n\n=================================Välkommen till lagerhantering 1.1\n=================================\n\n");
  
}


char ask_question_char(char *q, char *alt)
{
  printf("%s [%s]\n", q, alt);
 
  char alf = 0;
  int error = scanf(" %c", &alf);
  
  while ((strchr(alt, alf) == NULL && alt != NULL )|| error == 0){
      printf("Felaktig input '%c', försök igen om du vågar! [%s]\n", alf, alt);
      clear_stdin();
      error = scanf(" %c", &alf);
    } 

  clear_stdin();
  return alf;
}


int ask_question_int(char *q) 
{
  printf("%s", q);

  int num = 0;
  int tmp = scanf("%d", &num);
  while(tmp == 0 || num < 0){
      puts("Ogiltig inmatning, försök igen!");
      clear_stdin();
      tmp = scanf("%d", &num);
    }
  clear_stdin();
  return num;
}


char *ask_question_string(char *q,int ln){

  printf("%s",q);

  char *buffer;
  buffer = malloc(ln); 
  fgets (buffer, ln-1, stdin);
 
  if(buffer[strlen(buffer)-1] != '\0'){
    buffer[strlen(buffer)-1] = '\0';
  }

  return buffer;
}


shelf_t *ask_for_shelf()
{
  int count = ask_question_int("Antal:");
  char *place = ask_question_string("Hylla:",100);
  place[0] = toupper(place[0]);

  shelf_t *shlf = shelf_create(place,count);
  free(place);
  while(shlf == NULL){
    puts("Felaktig inmatning, välj en hylla.");
    char *place = ask_question_string("Hylla:",100);
    shlf = shelf_create(place,count);
    free(place);
  }
   
  return shlf;
}




void add_goods_interf(db_t *db){
  char *name    =   ask_question_string("Namn: ",100);
  good_t *good  =   db_get_good_with_key(db,name);

  if(good == NULL){
    //create new good
    char *desc   =  ask_question_string("Beskrivning:",100);
    int price    =  ask_question_int("Pris:");

    good = good_create(name,desc,price);
    db_insert_good(db,good);

  }else{
    free(name);
    puts("Hittade samma vara i databasen.");
    puts("Använder samma beskrivning och pris.");
    printf(" -- Beskrivning: %s \n",good_get_desc(good));
    printf(" -- Pris: %d \n",good_get_price(good));
  }
  //we have good 
  //now insert inte shelf 
    shelf_t *shelf = ask_for_shelf();
    good_insert_shelf(&good,shelf);
}

void print_good_with_index(void *good, int *index){
  good_t *g = good;
  printf("%d. %s\n",*index,good_get_name(g));
}


void list_goods(db_t *db){
  tree_traverse_in_order(db_get_goods(db),&print_good_with_index);
}


void print_shelf(void *shelf, int i){
  printf("%d                 ",i+1);
  printf("<%c%d>",shelf_get_alf(shelf),shelf_get_num(shelf));
  printf("%17dst\n",shelf_get_count(shelf));
}


void print_good(good_t *good){
  printf("\nNamn:%s\nBeskrivning:%s\nPris:%d\n",good_get_name(good),good_get_desc(good),good_get_price(good));

}

void print_shelves(good_t *good){
 puts("Varorna finns på hyllorna:");
   printf("\nId:               Hylla:               Antal:\n");
  list_traverse(good_get_shelves(good),&print_shelf);



}

void print_good_at_index(db_t *db,int i){
  good_t *g = db_get_good_at_index(db,i);
  if(g != NULL){
    print_good(g);
    print_shelves(g);
  }
}


void list_goods_interface(db_t *db){
  list_goods(db);
  int i = ask_question_int("Välj en vara:");
  print_good_at_index(db,i-1);

}


void remove_goods_interf(db_t *db){
  list_goods(db);
  int i = ask_question_int("Välj en vara att radera:");

  //print shelves with id

  
 good_t *good =  db_get_good_at_index(db,i-1);
  //välj en hylla att radera
  //osv
 
 print_shelves(good);

 int index = ask_question_int("Välj en hylla att radera:");
 void *shlv = NULL;
 list_t *list = good_get_shelves(good);
 list_remove(&list,index-1,&shlv);

 printf("REMOVE SHELF:%i ",shelf_get_count(shlv));
 shelf_dealloc(shlv);

}



void edit_good_interf(db_t *db){

  list_goods(db);
  int i = ask_question_int("Välj en vara att radera:");
  good_t *good =  db_get_good_at_index(db,i-1);
  print_good(good);

  char opt = ask_question_char("Vad vill du redigera? \n[N]amn\n[B]eskrivning\n[P]ris\n[A]vbryt","NBPA");
  switch(opt){
    case 'N':
      printf("Nuvarande namn:%s\n",good_get_name(good));
      char *new_name = ask_question_string("Nytt namn:",100);
      db_remove_good(db,good_get_name(good),false);
      good_set_name(&good,new_name);
      db_insert_good(db,good);
    break; 

    case 'B':
      printf("Nuvarande beskrivning:%s\n",good_get_name(good));
      char *desc = ask_question_string("Ny beskrivning:",100);
      good_set_desc(&good,desc);
      break;
     case 'P':
      printf("Nuvarande pris:%s\n",good_get_name(good));
      int price = ask_question_int("Nytt pris:");
      good_set_price(&good,price);
     break; 

     case 'A':
      return;

     break;

     default: 
     //start over
     puts("Felaktig input, försök igen.");
     edit_good_interf(db);
     break;

  }

  

}




