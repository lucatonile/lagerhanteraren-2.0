#ifndef __interface_h__
#define __interface_h__

#include "db.h"

/// \file interface.h
/// \author Casper Strömberg
/// \version 1.0
/// \date 2015-10-12

void print_welcome();


/// ask question that requires a int in return
/// \param q the question
/// \returns the inputed int
int ask_question_int(char *q);

/// add good 
void add_goods_interf(db_t *db);

void remove_goods_interf(db_t *db);

void list_goods_interface(db_t *db);

void edit_good_interf(db_t *db);

void regret_action_interf();


#endif