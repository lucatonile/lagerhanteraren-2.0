#include "interface.h"
#include "db.h"




int main_loop(db_t *db)
{
  int option = 0;
  option = ask_question_int("\n\nMenu\n1.Lägga till en vara \n2.Ta bort en vara \n3.Redigera en vara \n4.Ångra senaste ändringen \n5.Lista hela varukatalogen\n6.Packa en pall \n7.Avsluta \n\nVad vill du göra idag? _");
  
  switch(option)
    {
    case 1:
      add_goods_interf(db);
      break;
      
    case 2: 
      remove_goods_interf(db);
    break;

    case 3:
      edit_good_interf(db);
      break;
      
    case 4:
      //regret_action_interf();
      break;
      
    case 5:
      list_goods_interface(db);  
      break;
      
    case 6: 
      //packa pall
    db_dealloc(db);
      //pack_pallet_interf(db);


      break;
      
    case 7:

      return 0;
      break;

    default: 

    break;
    }
  
  return 1;
}


int main()
{


  db_t *db = db_new();
  print_welcome();

  while(main_loop(db));

  db_dealloc(db);
  return 0;
}

