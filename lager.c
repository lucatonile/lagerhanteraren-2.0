#define _GNU_SOURCE
#include "interface.h"
#include "input.h"
#include "db.h"
#include "pallet.h"
#include <stdio.h>




int main_loop(db_t *db)
{
    int option = 0;
    
    
   
    
    if(undoable(db)){
        option = Ask_int("\n\nMenu\n1.Add good \n2.Remove good \n3.Edit good \n4.Undo \n5.List goods\n6.Pack a pallet \n7.Exit \n\nWhat do you want to do? _");
    }else{
        option = Ask_int("\n\nMenu\n1.Add good \n2.Remove good \n3.Edit good\n5.List goods\n6.Pack a pallet \n7.Exit \n\nWhat do you want to do? _");
    }
    
    
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
            if(undoable(db))
            regret_action_interf(db);
           
            break;
        case 5:
            list_goods_interface(db);
            break;
        case 6:
            shopping_interf(db);
            break;
        case 7:
            return 0;
            break;
        default:
            break;
    }
    return 1;
}


int main(){
    db_t *db = db_new();
    print_welcome();
    
    
    while(main_loop(db));
    
    
    db_dealloc(db);
    
    return 0;
}

