#include <stdbool.h>
typedef union result result_t;
// data och kontrollerar om datat kan omvandlas
/// till avsedd typ
/// Exempel:
///   - valid_int
///   - valid_shelf
typedef bool (*v_f)(char *);

/// data och omvandlar det till avsedd typ, returnerar
/// en pekare till det nya datat
/// Exempel:
///   - str_to_int
///   - str_to_shelf
typedef result_t (*m_f)(char *);


#define Ask_int(q)  ask_question(q,valid_int, str_to_int, true).int_value;
#define Ask_str(q)  ask_question(q, NULL, str_to_str,false).ptr;
#define Ask_char(q) ask_question(q,valid_char, str_to_char,true).char_value;


#define Ask_name()    Ask_str("Name:")
#define Ask_desc()    Ask_str("Description:")
#define Ask_price()   Ask_int("Price:")
#define Ask_amount()  Ask_int("Amount:")
#define Ask_shelf()	  ask_question("Shelf:",valid_shelf, str_to_shelf,true).ptr;


bool valid_int(char *str);
bool valid_shelf(char *input);
bool valid_char(char *str);

result_t str_to_int(char *str);
result_t str_to_str(char *str);
result_t str_to_char(char *str);
result_t str_to_shelf(char *str);

//special 

char ask_question_char_with_constraints(char *q,char *s);


union result{
  void *ptr;
  int int_value;
  char char_value;
};






result_t ask_question(char *q, v_f validate, m_f convert, bool cleanup);

